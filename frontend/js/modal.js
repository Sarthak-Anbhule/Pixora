/**
 * PIXORA - Pin Detail Modal & Social Interaction System
 * Contributed by: Member 03 (Pin Modal Architecture & Social Mechanics)
 * 
 * Provides an expansive, responsive modal view for pins featuring high-resolution
 * media display, board selector, comment thread, like reactions, creator follow toggle,
 * and contextual "More to Explore" recommendations.
 */

class PinModal {
    static modalOverlay = null;
    static currentPinId = null;

    static init() {
        this.modalOverlay = document.getElementById('pin-detail-modal-overlay');
        if (!this.modalOverlay) return;

        // Backdrop click to close
        this.modalOverlay.addEventListener('click', (e) => {
            if (e.target === this.modalOverlay) {
                this.close();
            }
        });

        // ESC to close
        document.addEventListener('keydown', (e) => {
            if (e.key === 'Escape' && this.isOpen()) {
                this.close();
            }
        });
    }

    static isOpen() {
        return this.modalOverlay && this.modalOverlay.classList.contains('is-active');
    }

    /**
     * Open the modal for a specific pin
     */
    static open(pinId) {
        const pin = StorageManager.getPinById(pinId);
        if (!pin) return;

        this.currentPinId = pinId;
        if (!this.modalOverlay) this.init();

        const boards = StorageManager.getBoards();
        const isFollowing = StorageManager.isFollowing(pin.author.handle);
        const isSaved = pin.isSaved;
        const isLiked = pin.isLiked;

        // Render modal content
        const modalContainer = this.modalOverlay.querySelector('.modal-container');
        modalContainer.innerHTML = `
            <button class="modal-close-corner-btn" id="modal-close-btn" aria-label="Close modal">
                <svg viewBox="0 0 24 24" width="24" height="24" fill="none" stroke="currentColor" stroke-width="2.5"><line x1="18" y1="6" x2="6" y2="18"/><line x1="6" y1="6" x2="18" y2="18"/></svg>
            </button>

            <div class="pin-modal-split-layout">
                <!-- Media Column (Left) -->
                <div class="modal-media-col">
                    <div class="modal-image-wrapper">
                        <img 
                            src="${pin.imageUrl}" 
                            alt="${pin.title}" 
                            class="modal-pin-image"
                            onerror="MasonryFeed.handleImageError(this)" 
                        />
                        <div class="modal-media-actions">
                            <button class="glass-pill-btn" id="modal-download-btn" title="Download Image">
                                <svg viewBox="0 0 24 24" width="16" height="16" fill="none" stroke="currentColor" stroke-width="2.5"><path d="M21 15v4a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2v-4"/><polyline points="7 10 12 15 17 10"/><line x1="12" y1="15" x2="12" y2="3"/></svg>
                                <span>Save Image</span>
                            </button>
                            <a href="${pin.imageUrl}" target="_blank" rel="noopener noreferrer" class="glass-pill-btn" title="View Fullscreen">
                                <svg viewBox="0 0 24 24" width="16" height="16" fill="none" stroke="currentColor" stroke-width="2.5"><polyline points="15 3 21 3 21 9"/><polyline points="9 21 3 21 3 15"/><line x1="21" y1="3" x2="14" y2="10"/><line x1="3" y1="21" x2="10" y2="14"/></svg>
                                <span>Full Resolution</span>
                            </a>
                        </div>
                    </div>
                </div>

                <!-- Info & Discussion Column (Right) -->
                <div class="modal-info-col">
                    <!-- Top Action Bar -->
                    <div class="modal-header-actions">
                        <div class="board-selector-group">
                            <select id="modal-board-select" class="modal-board-dropdown" aria-label="Select board to save">
                                ${boards.map(b => `<option value="${b.title}" ${b.title === pin.board ? 'selected' : ''}>${b.title}</option>`).join('')}
                            </select>
                            <button id="modal-save-btn" class="pixora-btn-primary ${isSaved ? 'btn-saved-state' : ''}">
                                ${isSaved ? 'Saved' : 'Save'}
                            </button>
                        </div>
                        <div class="modal-utility-actions">
                            <button id="modal-share-btn" class="icon-circle-btn" title="Share pin">
                                <svg viewBox="0 0 24 24" width="18" height="18" fill="none" stroke="currentColor" stroke-width="2"><circle cx="18" cy="5" r="3"/><circle cx="6" cy="12" r="3"/><circle cx="18" cy="19" r="3"/><line x1="8.59" y1="13.51" x2="15.42" y2="17.49"/><line x1="15.41" y1="6.51" x2="8.59" y2="10.49"/></svg>
                            </button>
                        </div>
                    </div>

                    <!-- Scrollable Content Area -->
                    <div class="modal-scrollable-body">
                        ${pin.sourceUrl ? `
                            <a href="${pin.sourceUrl}" target="_blank" rel="noopener noreferrer" class="modal-source-link">
                                <svg viewBox="0 0 24 24" width="14" height="14" fill="none" stroke="currentColor" stroke-width="2"><path d="M10 13a5 5 0 0 0 7.54.54l3-3a5 5 0 0 0-7.07-7.07l-1.72 1.71"/><path d="M14 11a5 5 0 0 0-7.54-.54l-3 3a5 5 0 0 0 7.07 7.07l1.71-1.71"/></svg>
                                <span>${pin.sourceUrl.replace(/^https?:\/\//, '')}</span>
                            </a>
                        ` : ''}

                        <h1 class="modal-pin-title">${pin.title}</h1>
                        <p class="modal-pin-description">${pin.description || 'No description provided.'}</p>

                        <!-- Tags and Category -->
                        <div class="modal-tag-cloud">
                            <span class="modal-category-badge">${pin.category}</span>
                            ${(pin.tags || []).map(t => `<span class="modal-tag">#${t}</span>`).join('')}
                        </div>

                        <!-- Creator Card -->
                        <div class="modal-creator-card">
                            <div class="creator-left">
                                <img src="${pin.author.avatar}" alt="${pin.author.name}" class="creator-avatar" />
                                <div class="creator-meta">
                                    <div class="creator-name-row">
                                        <h4 class="creator-name">${pin.author.name}</h4>
                                        ${pin.author.verified ? `<span class="verified-badge" title="Verified Creator">✓</span>` : ''}
                                    </div>
                                    <span class="creator-followers" id="creator-followers-count">${(pin.author.followers || 1200).toLocaleString()} followers</span>
                                </div>
                            </div>
                            <button id="modal-follow-btn" class="pixora-btn-secondary ${isFollowing ? 'btn-following' : ''}">
                                ${isFollowing ? 'Following' : 'Follow'}
                            </button>
                        </div>

                        <!-- Comments Section -->
                        <div class="modal-comments-section">
                            <div class="comments-header">
                                <h3 class="comments-heading">Discussion (<span id="modal-comment-count">${(pin.comments || []).length}</span>)</h3>
                            </div>
                            
                            <div class="comments-list" id="modal-comments-list">
                                ${this.renderCommentsHtml(pin.comments || [])}
                            </div>
                        </div>
                    </div>

                    <!-- Sticky Bottom Action Footer -->
                    <div class="modal-sticky-footer">
                        <div class="modal-reactions-bar">
                            <div class="reactions-left">
                                <button id="modal-like-btn" class="reaction-heart-btn ${isLiked ? 'is-liked' : ''}">
                                    <svg viewBox="0 0 24 24" width="20" height="20" class="heart-icon" fill="${isLiked ? '#E60023' : 'none'}" stroke="${isLiked ? '#E60023' : 'currentColor'}" stroke-width="2"><path d="M19 14c1.49-1.46 3-3.21 3-5.5A5.5 5.5 0 0 0 16.5 3c-1.76 0-3 .5-4.5 2-1.5-1.5-2.74-2-4.5-2A5.5 5.5 0 0 0 2 8.5c0 2.3 1.5 4.05 3 5.5l7 7Z"/></svg>
                                    <span id="modal-likes-count">${pin.likes || 0}</span>
                                </button>
                                <span class="saves-stat">${pin.saves || 0} saves</span>
                            </div>
                        </div>

                        <!-- Comment input bar -->
                        <form id="modal-comment-form" class="comment-input-form">
                            <input 
                                type="text" 
                                id="modal-comment-input" 
                                class="comment-input-field" 
                                placeholder="Add a comment..." 
                                maxlength="280" 
                                autocomplete="off"
                            />
                            <div class="comment-emojis-row">
                                <button type="button" class="emoji-quick-btn" data-emoji="❤️">❤️</button>
                                <button type="button" class="emoji-quick-btn" data-emoji="✨">✨</button>
                                <button type="button" class="emoji-quick-btn" data-emoji="👏">👏</button>
                                <button type="button" class="emoji-quick-btn" data-emoji="🔥">🔥</button>
                            </div>
                            <button type="submit" class="comment-submit-btn" id="modal-submit-comment">Post</button>
                        </form>
                    </div>
                </div>
            </div>

            <!-- More Like This / Related Pins Row -->
            <div class="modal-related-section">
                <h3 class="related-title">More to Explore</h3>
                <div class="related-pins-grid" id="modal-related-grid"></div>
            </div>
        `;

        this.modalOverlay.classList.add('is-active');
        document.body.style.overflow = 'hidden';

        // Attach listeners inside modal
        this.attachModalListeners(pin);
        this.renderRelatedPins(pin);
    }

    static renderCommentsHtml(comments) {
        if (!comments || comments.length === 0) {
            return `
                <div class="empty-comments-state">
                    <p>No comments yet. Share what you think about this pin!</p>
                </div>
            `;
        }

        return comments.map(c => `
            <div class="comment-item">
                <img src="${c.user.avatar}" alt="${c.user.name}" class="comment-user-avatar" />
                <div class="comment-bubble">
                    <div class="comment-meta-row">
                        <span class="comment-user-name">${c.user.name}</span>
                        <span class="comment-timestamp">${c.timestamp || 'Recently'}</span>
                    </div>
                    <p class="comment-text">${c.text}</p>
                </div>
            </div>
        `).join('');
    }

    static attachModalListeners(pin) {
        const closeBtn = document.getElementById('modal-close-btn');
        if (closeBtn) closeBtn.addEventListener('click', () => this.close());

        // Board Save
        const saveBtn = document.getElementById('modal-save-btn');
        const boardSelect = document.getElementById('modal-board-select');
        if (saveBtn) {
            saveBtn.addEventListener('click', () => {
                const selectedBoard = boardSelect ? boardSelect.value : null;
                const isSaved = StorageManager.toggleSavePin(pin.id, selectedBoard);
                saveBtn.textContent = isSaved ? 'Saved' : 'Save';
                saveBtn.className = `pixora-btn-primary ${isSaved ? 'btn-saved-state' : ''}`;

                if (isSaved) {
                    ToastService.save(`Saved to "${selectedBoard || 'Profile'}"!`);
                } else {
                    ToastService.info('Removed from saved pins');
                }
                PixoraApp.syncCounters();
                PixoraApp.refreshCurrentView();
            });
        }

        // Like Button
        const likeBtn = document.getElementById('modal-like-btn');
        const likesCount = document.getElementById('modal-likes-count');
        if (likeBtn) {
            likeBtn.addEventListener('click', () => {
                const res = StorageManager.toggleLikePin(pin.id);
                if (likesCount) likesCount.textContent = res.likesCount;
                const heartSvg = likeBtn.querySelector('.heart-icon');

                if (res.isLiked) {
                    likeBtn.classList.add('is-liked');
                    heartSvg.setAttribute('fill', '#E60023');
                    heartSvg.setAttribute('stroke', '#E60023');
                    ToastService.heart('Liked pin');
                } else {
                    likeBtn.classList.remove('is-liked');
                    heartSvg.setAttribute('fill', 'none');
                    heartSvg.setAttribute('stroke', 'currentColor');
                }
                PixoraApp.refreshCurrentView();
            });
        }

        // Follow Button
        const followBtn = document.getElementById('modal-follow-btn');
        const followersCount = document.getElementById('creator-followers-count');
        if (followBtn) {
            followBtn.addEventListener('click', () => {
                const isFollowing = StorageManager.toggleFollow(pin.author.handle);
                followBtn.textContent = isFollowing ? 'Following' : 'Follow';
                followBtn.className = `pixora-btn-secondary ${isFollowing ? 'btn-following' : ''}`;
                
                const baseCount = pin.author.followers || 1200;
                const newCount = isFollowing ? baseCount + 1 : baseCount;
                if (followersCount) followersCount.textContent = `${newCount.toLocaleString()} followers`;

                ToastService.info(isFollowing ? `You are now following ${pin.author.name}` : `Unfollowed ${pin.author.name}`);
            });
        }

        // Download Image
        const downloadBtn = document.getElementById('modal-download-btn');
        if (downloadBtn) {
            downloadBtn.addEventListener('click', () => {
                MasonryFeed.downloadImage(pin.imageUrl, `${pin.title.toLowerCase().replace(/[^a-z0-9]/g, '-')}.jpg`);
            });
        }

        // Share Pin
        const shareBtn = document.getElementById('modal-share-btn');
        if (shareBtn) {
            shareBtn.addEventListener('click', () => {
                const url = `${window.location.origin}${window.location.pathname}#pin=${pin.id}`;
                if (navigator.clipboard) {
                    navigator.clipboard.writeText(url).then(() => {
                        ToastService.success('Pin link copied to clipboard!');
                    });
                } else {
                    ToastService.info('Pin link ready!');
                }
            });
        }

        // Emoji buttons
        const commentInput = document.getElementById('modal-comment-input');
        const emojiBtns = document.querySelectorAll('.emoji-quick-btn');
        emojiBtns.forEach(btn => {
            btn.addEventListener('click', () => {
                if (commentInput) {
                    commentInput.value += btn.getAttribute('data-emoji');
                    commentInput.focus();
                }
            });
        });

        // Add Comment Form
        const commentForm = document.getElementById('modal-comment-form');
        if (commentForm) {
            commentForm.addEventListener('submit', (e) => {
                e.preventDefault();
                const text = commentInput ? commentInput.value.trim() : '';
                if (!text) return;

                const newComment = StorageManager.addComment(pin.id, text);
                if (newComment) {
                    commentInput.value = '';
                    const commentsList = document.getElementById('modal-comments-list');
                    const updatedPin = StorageManager.getPinById(pin.id);
                    if (commentsList && updatedPin) {
                        commentsList.innerHTML = this.renderCommentsHtml(updatedPin.comments || []);
                    }
                    const countSpan = document.getElementById('modal-comment-count');
                    if (countSpan && updatedPin) {
                        countSpan.textContent = (updatedPin.comments || []).length;
                    }
                    ToastService.success('Comment posted!');
                }
            });
        }
    }

    /**
     * Render related pins in the bottom of modal
     */
    static renderRelatedPins(currentPin) {
        const grid = document.getElementById('modal-related-grid');
        if (!grid) return;

        const allPins = StorageManager.getPins();
        const related = allPins
            .filter(p => p.id !== currentPin.id && (p.category === currentPin.category || p.board === currentPin.board))
            .slice(0, 6);

        if (related.length === 0) {
            grid.innerHTML = '<p class="related-empty">Explore the feed for more pins in this style.</p>';
            return;
        }

        grid.innerHTML = related.map(p => `
            <div class="related-pin-card" onclick="PinModal.open('${p.id}')">
                <img src="${p.imageUrl}" alt="${p.title}" class="related-pin-img" loading="lazy" />
                <div class="related-pin-info">
                    <span class="related-pin-title">${p.title}</span>
                </div>
            </div>
        `).join('');
    }

    /**
     * Close the modal
     */
    static close() {
        if (!this.modalOverlay) return;
        this.modalOverlay.classList.remove('is-active');
        document.body.style.overflow = '';
        this.currentPinId = null;
    }
}
