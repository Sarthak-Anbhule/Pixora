/**
 * PIXORA - Storage & State Persistence Layer
 * Contributed by: Member 07 (Storage & State Persistence)
 * 
 * Manages all local state persistence with localStorage, robust fallback handling,
 * pin querying, mutations (saves, likes, comments, boards, profile edits).
 */

class StorageManager {
    static apiBase = (typeof window !== 'undefined' && window.location && window.location.origin && window.location.origin.includes('8080')) ? '' : 'http://localhost:8080';
    static isBackendConnected = false;

    static STORAGE_KEYS = {
        PINS: 'pixora_pins_v1',
        SAVED: 'pixora_saved_pin_ids_v1',
        LIKED: 'pixora_liked_pin_ids_v1',
        BOARDS: 'pixora_boards_v1',
        PROFILE: 'pixora_user_profile_v1',
        FOLLOWING: 'pixora_following_handles_v1',
        CREATED: 'pixora_created_pin_ids_v1'
    };

    /**
     * Initialize storage and attempt handshake with C++ backend
     */
    static init() {
        this.checkBackendConnection();
        try {
            if (!localStorage.getItem(this.STORAGE_KEYS.PINS)) {
                localStorage.setItem(this.STORAGE_KEYS.PINS, JSON.stringify(INITIAL_PINS));
            }
            if (!localStorage.getItem(this.STORAGE_KEYS.SAVED)) {
                const defaultSaved = INITIAL_PINS.filter(p => p.isSaved).map(p => p.id);
                localStorage.setItem(this.STORAGE_KEYS.SAVED, JSON.stringify(defaultSaved));
            }
            if (!localStorage.getItem(this.STORAGE_KEYS.LIKED)) {
                const defaultLiked = INITIAL_PINS.filter(p => p.isLiked).map(p => p.id);
                localStorage.setItem(this.STORAGE_KEYS.LIKED, JSON.stringify(defaultLiked));
            }
            if (!localStorage.getItem(this.STORAGE_KEYS.BOARDS)) {
                localStorage.setItem(this.STORAGE_KEYS.BOARDS, JSON.stringify(INITIAL_BOARDS));
            }
            if (!localStorage.getItem(this.STORAGE_KEYS.PROFILE)) {
                localStorage.setItem(this.STORAGE_KEYS.PROFILE, JSON.stringify(INITIAL_PROFILE));
            }
            if (!localStorage.getItem(this.STORAGE_KEYS.FOLLOWING)) {
                localStorage.setItem(this.STORAGE_KEYS.FOLLOWING, JSON.stringify(['kasperlind', 'oliverwild']));
            }
            if (!localStorage.getItem(this.STORAGE_KEYS.CREATED)) {
                // Pins created by Elena Vance initially
                const userCreated = INITIAL_PINS.filter(p => p.author.handle === 'elenavance').map(p => p.id);
                localStorage.setItem(this.STORAGE_KEYS.CREATED, JSON.stringify(userCreated));
            }
        } catch (e) {
            console.warn('LocalStorage unavailable or disabled, continuing with memory cache:', e);
        }
    }

    static checkBackendConnection() {
        if (typeof fetch === 'undefined') return;
        fetch(`${this.apiBase}/api/pins`)
            .then(res => res.json())
            .then(data => {
                if (Array.isArray(data) && data.length > 0) {
                    this.isBackendConnected = true;
                    console.log('%c⚡ Connected to PIXORA C++ Backend Server! ⚡', 'color: #10B981; font-weight: bold;');
                    this.setRaw(this.STORAGE_KEYS.PINS, data);
                    if (typeof PixoraApp !== 'undefined' && PixoraApp.refreshCurrentView) {
                        PixoraApp.refreshCurrentView();
                    }
                }
            })
            .catch(() => {
                // Running in standalone client mode
            });
    }

    static getRaw(key, fallback = []) {
        try {
            const data = localStorage.getItem(key);
            return data ? JSON.parse(data) : fallback;
        } catch (e) {
            console.error(`Error parsing ${key} from localStorage:`, e);
            return fallback;
        }
    }

    static setRaw(key, value) {
        try {
            localStorage.setItem(key, JSON.stringify(value));
            return true;
        } catch (e) {
            console.error(`Error writing ${key} to localStorage:`, e);
            return false;
        }
    }

    /**
     * Get all pins with updated saved & liked status
     */
    static getPins() {
        const pins = this.getRaw(this.STORAGE_KEYS.PINS, INITIAL_PINS);
        const savedIds = new Set(this.getSavedPinIds());
        const likedIds = new Set(this.getLikedPinIds());

        return pins.map(pin => ({
            ...pin,
            isSaved: savedIds.has(pin.id),
            isLiked: likedIds.has(pin.id)
        }));
    }

    static getPinById(id) {
        const pins = this.getPins();
        return pins.find(p => p.id === id) || null;
    }

    static getSavedPinIds() {
        return this.getRaw(this.STORAGE_KEYS.SAVED, []);
    }

    static getLikedPinIds() {
        return this.getRaw(this.STORAGE_KEYS.LIKED, []);
    }

    static getCreatedPinIds() {
        return this.getRaw(this.STORAGE_KEYS.CREATED, []);
    }

    /**
     * Get array of all saved pins
     */
    static getSavedPins() {
        const pins = this.getPins();
        const savedIds = new Set(this.getSavedPinIds());
        return pins.filter(p => savedIds.has(p.id));
    }

    /**
     * Get pins created by current user
     */
    static getCreatedPins() {
        const pins = this.getPins();
        const createdIds = new Set(this.getCreatedPinIds());
        return pins.filter(p => createdIds.has(p.id));
    }

    /**
     * Toggle Save / Unsave a pin
     * @returns {boolean} isSaved now
     */
    static toggleSavePin(pinId, boardName = null) {
        const savedIds = this.getSavedPinIds();
        const pins = this.getPins();
        const targetPin = pins.find(p => p.id === pinId);
        let isSaved = false;

        const index = savedIds.indexOf(pinId);
        if (index > -1) {
            // Unsave
            savedIds.splice(index, 1);
            if (targetPin) {
                targetPin.saves = Math.max(0, (targetPin.saves || 1) - 1);
            }
            isSaved = false;
        } else {
            // Save
            savedIds.unshift(pinId);
            if (targetPin) {
                targetPin.saves = (targetPin.saves || 0) + 1;
                if (boardName) {
                    targetPin.board = boardName;
                }
            }
            isSaved = true;
        }

        this.setRaw(this.STORAGE_KEYS.SAVED, savedIds);
        this.setRaw(this.STORAGE_KEYS.PINS, pins);

        // Update profile saves count
        const profile = this.getProfile();
        profile.savesCount = savedIds.length;
        this.setRaw(this.STORAGE_KEYS.PROFILE, profile);

        // Sync with C++ backend
        if (this.isBackendConnected) {
            fetch(`${this.apiBase}/api/pins/${pinId}/save`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ board: boardName || '' })
            }).catch(() => {});
        }

        return isSaved;
    }

    /**
     * Toggle Like / Unlike a pin
     * @returns {boolean} isLiked now
     */
    static toggleLikePin(pinId) {
        const likedIds = this.getLikedPinIds();
        const pins = this.getPins();
        const targetPin = pins.find(p => p.id === pinId);
        let isLiked = false;

        const index = likedIds.indexOf(pinId);
        if (index > -1) {
            likedIds.splice(index, 1);
            if (targetPin) targetPin.likes = Math.max(0, (targetPin.likes || 1) - 1);
            isLiked = false;
        } else {
            likedIds.push(pinId);
            if (targetPin) targetPin.likes = (targetPin.likes || 0) + 1;
            isLiked = true;
        }

        this.setRaw(this.STORAGE_KEYS.LIKED, likedIds);
        this.setRaw(this.STORAGE_KEYS.PINS, pins);

        // Sync with C++ backend
        if (this.isBackendConnected) {
            fetch(`${this.apiBase}/api/pins/${pinId}/like`, { method: 'POST' }).catch(() => {});
        }

        return { isLiked, likesCount: targetPin ? targetPin.likes : 0 };
    }

    /**
     * Add a comment to a pin
     */
    static addComment(pinId, commentText) {
        if (!commentText || !commentText.trim()) return null;

        const pins = this.getPins();
        const targetPin = pins.find(p => p.id === pinId);
        if (!targetPin) return null;

        const profile = this.getProfile();
        const newComment = {
            id: 'c-' + Date.now(),
            user: {
                name: profile.name,
                avatar: profile.avatar
            },
            text: commentText.trim(),
            timestamp: 'Just now'
        };

        if (!targetPin.comments) targetPin.comments = [];
        targetPin.comments.push(newComment);

        this.setRaw(this.STORAGE_KEYS.PINS, pins);

        // Sync with C++ backend
        if (this.isBackendConnected) {
            fetch(`${this.apiBase}/api/pins/${pinId}/comment`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ text: commentText.trim() })
            }).catch(() => {});
        }

        return newComment;
    }

    /**
     * Create and store a new pin
     */
    static createPin(pinData) {
        const pins = this.getPins();
        const profile = this.getProfile();

        const newPin = {
            id: 'pin-' + Date.now(),
            title: pinData.title || 'Untitled Pin',
            description: pinData.description || '',
            imageUrl: pinData.imageUrl,
            aspectRatio: pinData.aspectRatio || 'medium',
            height: pinData.height || 480,
            category: pinData.category || 'all',
            board: pinData.board || 'Creative Inspiration',
            tags: pinData.tags || [],
            sourceUrl: pinData.sourceUrl || '',
            likes: 0,
            saves: 1,
            isLiked: false,
            isSaved: true,
            author: {
                name: profile.name,
                handle: profile.handle,
                avatar: profile.avatar,
                verified: true,
                followers: profile.followersCount
            },
            comments: [],
            createdAt: new Date().toISOString().split('T')[0]
        };

        // Add to front of pins list
        pins.unshift(newPin);
        this.setRaw(this.STORAGE_KEYS.PINS, pins);

        // Auto-save to user saved pins
        const savedIds = this.getSavedPinIds();
        savedIds.unshift(newPin.id);
        this.setRaw(this.STORAGE_KEYS.SAVED, savedIds);

        // Add to user created pins
        const createdIds = this.getCreatedPinIds();
        createdIds.unshift(newPin.id);
        this.setRaw(this.STORAGE_KEYS.CREATED, createdIds);

        // Update board pin count if board exists
        const boards = this.getBoards();
        const board = boards.find(b => b.title.toLowerCase() === newPin.board.toLowerCase());
        if (board) {
            board.pinCount = (board.pinCount || 0) + 1;
            board.coverImage = newPin.imageUrl;
            this.setRaw(this.STORAGE_KEYS.BOARDS, boards);
        }

        // Sync with C++ backend
        if (this.isBackendConnected) {
            fetch(`${this.apiBase}/api/pins`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify(newPin)
            }).catch(() => {});
        }

        return newPin;
    }

    /**
     * Get Boards
     */
    static getBoards() {
        return this.getRaw(this.STORAGE_KEYS.BOARDS, INITIAL_BOARDS);
    }

    /**
     * Create a new Board
     */
    static createBoard({ title, description, isPrivate, coverImage }) {
        if (!title || !title.trim()) return null;

        const boards = this.getBoards();
        const newBoard = {
            id: 'board-' + Date.now(),
            title: title.trim(),
            description: description ? description.trim() : '',
            coverImage: coverImage || 'https://images.unsplash.com/photo-1618005182384-a83a8bd57fbe?auto=format&fit=crop&w=800&q=80',
            pinCount: 0,
            isPrivate: Boolean(isPrivate),
            createdAt: new Date().toISOString().split('T')[0]
        };

        boards.push(newBoard);
        this.setRaw(this.STORAGE_KEYS.BOARDS, boards);
        return newBoard;
    }

    /**
     * Get User Profile
     */
    static getProfile() {
        return this.getRaw(this.STORAGE_KEYS.PROFILE, INITIAL_PROFILE);
    }

    /**
     * Update User Profile
     */
    static updateProfile(updatedData) {
        const current = this.getProfile();
        const updated = { ...current, ...updatedData };
        this.setRaw(this.STORAGE_KEYS.PROFILE, updated);
        return updated;
    }

    /**
     * Follow/Unfollow a user
     */
    static toggleFollow(handle) {
        const following = this.getRaw(this.STORAGE_KEYS.FOLLOWING, []);
        const idx = following.indexOf(handle);
        let isFollowing = false;

        if (idx > -1) {
            following.splice(idx, 1);
            isFollowing = false;
        } else {
            following.push(handle);
            isFollowing = true;
        }

        this.setRaw(this.STORAGE_KEYS.FOLLOWING, following);

        // Update profile following count
        const profile = this.getProfile();
        profile.followingCount = following.length;
        this.setRaw(this.STORAGE_KEYS.PROFILE, profile);

        return isFollowing;
    }

    static isFollowing(handle) {
        const following = this.getRaw(this.STORAGE_KEYS.FOLLOWING, []);
        return following.includes(handle);
    }

    /**
     * Reset everything to factory demo state
     */
    static resetToDefaults() {
        try {
            localStorage.removeItem(this.STORAGE_KEYS.PINS);
            localStorage.removeItem(this.STORAGE_KEYS.SAVED);
            localStorage.removeItem(this.STORAGE_KEYS.LIKED);
            localStorage.removeItem(this.STORAGE_KEYS.BOARDS);
            localStorage.removeItem(this.STORAGE_KEYS.PROFILE);
            localStorage.removeItem(this.STORAGE_KEYS.FOLLOWING);
            localStorage.removeItem(this.STORAGE_KEYS.CREATED);
            this.init();
            return true;
        } catch (e) {
            console.error('Failed to reset storage:', e);
            return false;
        }
    }
}
