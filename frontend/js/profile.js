/**
 * PIXORA - User Profile & Boards Management System
 * Contributed by: Member 05 (User Profile Architecture & Board Collections)
 * 
 * Manages user profile display, profile editing, statistics syncing, tab switching
 * (Created / Saved / Boards), board collection rendering, and custom board creation.
 */

class ProfileManager {
    static currentTab = 'saved'; // 'created' | 'saved' | 'boards'
    static activeBoardFilter = null;

    static init() {
        this.renderProfileHeader();
        this.setupTabListeners();
        this.setupEditProfileModal();
        this.setupCreateBoardModal();
    }

    /**
     * Render Profile Header with current user data
     */
    static renderProfileHeader() {
        const profile = StorageManager.getProfile();
        const headerContainer = document.getElementById('profile-header-container');
        if (!headerContainer) return;

        headerContainer.innerHTML = `
            <div class="profile-cover-banner" style="background-image: url('${profile.coverImage}');">
                <div class="banner-gradient-overlay"></div>
            </div>
            
            <div class="profile-card-wrapper">
                <div class="profile-avatar-container">
                    <img src="${profile.avatar}" alt="${profile.name}" class="profile-main-avatar" onerror="this.src='https://images.unsplash.com/photo-1534528741775-53994a69daeb?auto=format&fit=crop&w=400&q=80'" />
                </div>

                <div class="profile-details">
                    <div class="profile-title-row">
                        <h1 class="profile-display-name">${profile.name}</h1>
                        <span class="profile-verified-icon" title="Verified Creator">✓</span>
                    </div>
                    <span class="profile-handle">@${profile.handle}</span>
                    <p class="profile-bio">${profile.bio}</p>

                    <div class="profile-meta-row">
                        ${profile.location ? `
                            <span class="profile-meta-item">
                                <svg viewBox="0 0 24 24" width="14" height="14" fill="none" stroke="currentColor" stroke-width="2"><path d="M20 10c0 6-8 12-8 12s-8-6-8-12a8 8 0 0 1 16 0Z"/><circle cx="12" cy="10" r="3"/></svg>
                                ${profile.location}
                            </span>
                        ` : ''}
                        ${profile.website ? `
                            <a href="${profile.website}" target="_blank" rel="noopener noreferrer" class="profile-meta-item profile-website-link">
                                <svg viewBox="0 0 24 24" width="14" height="14" fill="none" stroke="currentColor" stroke-width="2"><path d="M10 13a5 5 0 0 0 7.54.54l3-3a5 5 0 0 0-7.07-7.07l-1.72 1.71"/><path d="M14 11a5 5 0 0 0-7.54-.54l-3 3a5 5 0 0 0 7.07 7.07l1.71-1.71"/></svg>
                                ${profile.website.replace(/^https?:\/\//, '')}
                            </a>
                        ` : ''}
                    </div>

                    <div class="profile-stats-row">
                        <div class="stat-item">
                            <strong class="stat-number" id="profile-followers-stat">${(profile.followersCount || 1840).toLocaleString()}</strong>
                            <span class="stat-label">Followers</span>
                        </div>
                        <div class="stat-divider">·</div>
                        <div class="stat-item">
                            <strong class="stat-number" id="profile-following-stat">${profile.followingCount || 392}</strong>
                            <span class="stat-label">Following</span>
                        </div>
                        <div class="stat-divider">·</div>
                        <div class="stat-item">
                            <strong class="stat-number" id="profile-saves-stat">${StorageManager.getSavedPinIds().length}</strong>
                            <span class="stat-label">Saved</span>
                        </div>
                    </div>

                    <div class="profile-actions-row">
                        <button class="pixora-btn-secondary" id="open-edit-profile-btn">
                            <svg viewBox="0 0 24 24" width="16" height="16" fill="none" stroke="currentColor" stroke-width="2"><path d="M17 3a2.85 2.83 0 1 1 4 4L7.5 20.5 2 22l1.5-5.5Z"/></svg>
                            Edit Profile
                        </button>
                        <button class="pixora-btn-secondary" id="share-profile-btn">
                            <svg viewBox="0 0 24 24" width="16" height="16" fill="none" stroke="currentColor" stroke-width="2"><circle cx="18" cy="5" r="3"/><circle cx="6" cy="12" r="3"/><circle cx="18" cy="19" r="3"/><line x1="8.59" y1="13.51" x2="15.42" y2="17.49"/><line x1="15.41" y1="6.51" x2="8.59" y2="10.49"/></svg>
                            Share
                        </button>
                    </div>
                </div>
            </div>
        `;

        // Attach buttons in header
        const editBtn = document.getElementById('open-edit-profile-btn');
        if (editBtn) editBtn.addEventListener('click', () => this.openEditProfileModal());

        const shareBtn = document.getElementById('share-profile-btn');
        if (shareBtn) {
            shareBtn.addEventListener('click', () => {
                if (navigator.clipboard) {
                    navigator.clipboard.writeText(window.location.href).then(() => {
                        ToastService.success('Profile URL copied to clipboard!');
                    });
                } else {
                    ToastService.info('Profile link ready to share');
                }
            });
        }
    }

    /**
     * Switch Profile Tab
     */
    static setupTabListeners() {
        const tabBtns = document.querySelectorAll('.profile-tab-btn');
        tabBtns.forEach(btn => {
            btn.addEventListener('click', () => {
                tabBtns.forEach(b => b.classList.remove('is-active'));
                btn.classList.add('is-active');
                this.currentTab = btn.getAttribute('data-tab');
                this.activeBoardFilter = null;
                this.renderTabContent();
            });
        });
    }

    /**
     * Render the active tab content
     */
    static renderTabContent() {
        const contentContainer = document.getElementById('profile-tab-content');
        if (!contentContainer) return;

        if (this.currentTab === 'created') {
            const createdPins = StorageManager.getCreatedPins();
            contentContainer.innerHTML = '<div class="pins-grid-layout" id="profile-created-grid"></div>';
            MasonryFeed.container = document.getElementById('profile-created-grid');
            MasonryFeed.renderPins(createdPins, "You haven't created any pins yet.");
        } else if (this.currentTab === 'saved') {
            const savedPins = StorageManager.getSavedPins();
            contentContainer.innerHTML = '<div class="pins-grid-layout" id="profile-saved-grid"></div>';
            MasonryFeed.container = document.getElementById('profile-saved-grid');
            MasonryFeed.renderPins(savedPins, "You haven't saved any pins yet. Tap the red 'Save' button on any pin!");
        } else if (this.currentTab === 'boards') {
            if (this.activeBoardFilter) {
                this.renderBoardSpecificPins(contentContainer);
            } else {
                this.renderBoardsList(contentContainer);
            }
        }
    }

    /**
     * Render Boards collection list
     */
    static renderBoardsList(container) {
        const boards = StorageManager.getBoards();
        const allPins = StorageManager.getPins();

        // Count pins for each board dynamically
        boards.forEach(b => {
            const count = allPins.filter(p => p.board && p.board.toLowerCase() === b.title.toLowerCase() && p.isSaved).length;
            b.dynamicCount = count;
        });

        container.innerHTML = `
            <div class="boards-top-bar">
                <span class="boards-count-badge">${boards.length} Collections</span>
                <button class="pixora-btn-primary" id="open-create-board-modal-btn">
                    <svg viewBox="0 0 24 24" width="18" height="18" fill="none" stroke="currentColor" stroke-width="2.5"><line x1="12" y1="5" x2="12" y2="19"/><line x1="5" y1="12" x2="19" y2="12"/></svg>
                    Create Board
                </button>
            </div>
            <div class="boards-grid-layout">
                ${boards.map(b => `
                    <div class="board-card" data-board-title="${b.title}" tabindex="0">
                        <div class="board-cover-wrapper">
                            <img src="${b.coverImage}" alt="${b.title}" class="board-cover-img" onerror="MasonryFeed.handleImageError(this)" />
                            ${b.isPrivate ? `<span class="board-private-badge" title="Secret board">🔒 Secret</span>` : ''}
                        </div>
                        <div class="board-meta">
                            <h3 class="board-title">${b.title}</h3>
                            <span class="board-count">${b.dynamicCount || b.pinCount || 0} Pins</span>
                        </div>
                    </div>
                `).join('')}
            </div>
        `;

        // Card clicks
        const boardCards = container.querySelectorAll('.board-card');
        boardCards.forEach(card => {
            card.addEventListener('click', () => {
                const title = card.getAttribute('data-board-title');
                this.activeBoardFilter = title;
                this.renderTabContent();
            });
        });

        const createBoardBtn = document.getElementById('open-create-board-modal-btn');
        if (createBoardBtn) {
            createBoardBtn.addEventListener('click', () => this.openCreateBoardModal());
        }
    }

    /**
     * Render pins inside a selected board
     */
    static renderBoardSpecificPins(container) {
        const allPins = StorageManager.getPins();
        const boardPins = allPins.filter(p => p.board && p.board.toLowerCase() === this.activeBoardFilter.toLowerCase() && p.isSaved);

        container.innerHTML = `
            <div class="board-detail-header">
                <button class="back-to-boards-btn" id="back-to-boards-btn">
                    <svg viewBox="0 0 24 24" width="20" height="20" fill="none" stroke="currentColor" stroke-width="2.5"><polyline points="15 18 9 12 15 6"/></svg>
                    <span>All Boards</span>
                </button>
                <div class="board-title-group">
                    <h2 class="active-board-heading">${this.activeBoardFilter}</h2>
                    <span class="active-board-count">${boardPins.length} Saved Pins</span>
                </div>
            </div>
            <div class="pins-grid-layout" id="board-filtered-grid"></div>
        `;

        document.getElementById('back-to-boards-btn').addEventListener('click', () => {
            this.activeBoardFilter = null;
            this.renderTabContent();
        });

        MasonryFeed.container = document.getElementById('board-filtered-grid');
        MasonryFeed.renderPins(boardPins, `No pins saved in "${this.activeBoardFilter}" yet.`);
    }

    /**
     * Edit Profile Modal logic
     */
    static setupEditProfileModal() {
        const modal = document.getElementById('edit-profile-modal');
        const form = document.getElementById('edit-profile-form');
        const closeBtn = document.getElementById('close-edit-profile-modal');
        if (!modal || !form) return;

        closeBtn.addEventListener('click', () => modal.classList.remove('is-active'));
        modal.addEventListener('click', (e) => {
            if (e.target === modal) modal.classList.remove('is-active');
        });

        form.addEventListener('submit', (e) => {
            e.preventDefault();
            const name = document.getElementById('edit-profile-name').value.trim();
            const bio = document.getElementById('edit-profile-bio').value.trim();
            const location = document.getElementById('edit-profile-location').value.trim();
            const website = document.getElementById('edit-profile-website').value.trim();
            const avatar = document.getElementById('edit-profile-avatar').value.trim();

            if (!name) {
                ToastService.error('Name cannot be empty');
                return;
            }

            StorageManager.updateProfile({
                name,
                bio,
                location,
                website,
                avatar: avatar || INITIAL_PROFILE.avatar
            });

            this.renderProfileHeader();
            modal.classList.remove('is-active');
            ToastService.success('Profile updated successfully!');
            PixoraApp.syncCounters();
        });
    }

    static openEditProfileModal() {
        const modal = document.getElementById('edit-profile-modal');
        if (!modal) return;

        const profile = StorageManager.getProfile();
        document.getElementById('edit-profile-name').value = profile.name;
        document.getElementById('edit-profile-bio').value = profile.bio;
        document.getElementById('edit-profile-location').value = profile.location || '';
        document.getElementById('edit-profile-website').value = profile.website || '';
        document.getElementById('edit-profile-avatar').value = profile.avatar;

        modal.classList.add('is-active');
    }

    /**
     * Create Board Modal logic
     */
    static setupCreateBoardModal() {
        const modal = document.getElementById('create-board-modal');
        const form = document.getElementById('create-board-form');
        const closeBtn = document.getElementById('close-create-board-modal');
        if (!modal || !form) return;

        closeBtn.addEventListener('click', () => modal.classList.remove('is-active'));
        modal.addEventListener('click', (e) => {
            if (e.target === modal) modal.classList.remove('is-active');
        });

        form.addEventListener('submit', (e) => {
            e.preventDefault();
            const title = document.getElementById('new-board-title').value.trim();
            const description = document.getElementById('new-board-desc').value.trim();
            const isPrivate = document.getElementById('new-board-private').checked;

            if (!title) {
                ToastService.error('Please name your board.');
                return;
            }

            const newBoard = StorageManager.createBoard({
                title,
                description,
                isPrivate
            });

            if (newBoard) {
                form.reset();
                modal.classList.remove('is-active');
                ToastService.success(`Board "${newBoard.title}" created!`);
                PinCreator.setupBoardSelector();
                this.renderTabContent();
            }
        });
    }

    static openCreateBoardModal() {
        const modal = document.getElementById('create-board-modal');
        if (modal) modal.classList.add('is-active');
    }
}
