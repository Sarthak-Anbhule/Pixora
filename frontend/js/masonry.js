/**
 * PIXORA - Masonry Grid & Pin Rendering Engine
 * Contributed by: Member 02 (Masonry Grid & Pin Feed Architecture)
 * 
 * Generates dynamic, Pinterest-style staggered masonry columns, handles card
 * hover states, quick actions (save, like, share, download), and image fallbacks.
 */

class MasonryFeed {
    static container = null;

    static init(containerId = 'pins-masonry-grid') {
        this.container = document.getElementById(containerId);
    }

    /**
     * Render an array of pins into the grid
     */
    static renderPins(pins, emptyMessage = 'No pins found in this collection.') {
        if (!this.container) this.init();
        if (!this.container) return;

        if (!pins || pins.length === 0) {
            this.container.innerHTML = `
                <div class="empty-state-container">
                    <div class="empty-state-icon">
                        <svg viewBox="0 0 24 24" width="48" height="48" fill="none" stroke="currentColor" stroke-width="1.5">
                            <rect width="18" height="18" x="3" y="3" rx="2" ry="2"/>
                            <circle cx="9" cy="9" r="2"/>
                            <path d="m21 15-3.086-3.086a2 2 0 0 0-2.828 0L6 21"/>
                        </svg>
                    </div>
                    <h3 class="empty-state-title">${emptyMessage}</h3>
                    <p class="empty-state-desc">Try exploring other categories or create your own inspiring pin!</p>
                    <button class="pixora-btn-primary" onclick="PixoraApp.navigateTo('create')">
                        <svg viewBox="0 0 24 24" width="18" height="18" fill="none" stroke="currentColor" stroke-width="2.5"><line x1="12" y1="5" x2="12" y2="19"/><line x1="5" y1="12" x2="19" y2="12"/></svg>
                        Create a Pin
                    </button>
                </div>
            `;
            return;
        }

        // Render cards
        const cardsHtml = pins.map(pin => this.createPinCardHtml(pin)).join('');
        this.container.innerHTML = cardsHtml;

        // Attach event listeners to card interactive elements
        this.attachEventListeners();
    }

    /**
     * Generate HTML for a single pin card
     */
    static createPinCardHtml(pin) {
        const isSaved = pin.isSaved;
        const isLiked = pin.isLiked;
        const saveBtnText = isSaved ? 'Saved' : 'Save';
        const saveBtnClass = isSaved ? 'pin-btn-saved' : 'pin-btn-save';

        // Extract domain from sourceUrl
        let domain = '';
        if (pin.sourceUrl) {
            try {
                domain = new URL(pin.sourceUrl).hostname.replace('www.', '');
            } catch (e) {
                domain = pin.sourceUrl;
            }
        }

        return `
            <div class="pin-card" data-pin-id="${pin.id}" tabindex="0" role="article" aria-label="${pin.title}">
                <div class="pin-media-wrapper">
                    <img 
                        src="${pin.imageUrl}" 
                        alt="${pin.title}" 
                        class="pin-image" 
                        loading="lazy"
                        onerror="MasonryFeed.handleImageError(this)"
                    />
                    
                    <!-- Hover overlay with quick actions -->
                    <div class="pin-overlay">
                        <div class="overlay-top">
                            ${pin.board ? `<span class="pin-board-tag">${pin.board}</span>` : '<span></span>'}
                            <button class="pin-action-btn ${saveBtnClass}" data-action="save" data-pin-id="${pin.id}">
                                ${saveBtnText}
                            </button>
                        </div>
                        <div class="overlay-bottom">
                            ${domain ? `
                                <a href="${pin.sourceUrl}" target="_blank" rel="noopener noreferrer" class="pin-source-badge" data-action="link">
                                    <svg viewBox="0 0 24 24" width="12" height="12" fill="none" stroke="currentColor" stroke-width="2.5"><path d="M10 13a5 5 0 0 0 7.54.54l3-3a5 5 0 0 0-7.07-7.07l-1.72 1.71"/><path d="M14 11a5 5 0 0 0-7.54-.54l-3 3a5 5 0 0 0 7.07 7.07l1.71-1.71"/></svg>
                                    <span>${domain}</span>
                                </a>
                            ` : '<span></span>'}
                            <div class="overlay-icons-group">
                                <button class="pin-icon-btn" data-action="download" data-pin-id="${pin.id}" title="Download image" aria-label="Download">
                                    <svg viewBox="0 0 24 24" width="16" height="16" fill="none" stroke="currentColor" stroke-width="2.5"><path d="M21 15v4a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2v-4"/><polyline points="7 10 12 15 17 10"/><line x1="12" y1="15" x2="12" y2="3"/></svg>
                                </button>
                                <button class="pin-icon-btn" data-action="share" data-pin-id="${pin.id}" title="Copy Link" aria-label="Share">
                                    <svg viewBox="0 0 24 24" width="16" height="16" fill="none" stroke="currentColor" stroke-width="2.5"><circle cx="18" cy="5" r="3"/><circle cx="6" cy="12" r="3"/><circle cx="18" cy="19" r="3"/><line x1="8.59" y1="13.51" x2="15.42" y2="17.49"/><line x1="15.41" y1="6.51" x2="8.59" y2="10.49"/></svg>
                                </button>
                            </div>
                        </div>
                    </div>
                </div>

                <!-- Pin Card Meta Details -->
                <div class="pin-card-meta">
                    <h3 class="pin-title">${pin.title}</h3>
                    <div class="pin-author-row">
                        <div class="pin-author-info">
                            <img src="${pin.author.avatar}" alt="${pin.author.name}" class="pin-author-avatar" onerror="this.src='https://images.unsplash.com/photo-1534528741775-53994a69daeb?auto=format&fit=crop&w=100&q=80'" />
                            <span class="pin-author-name">${pin.author.name}</span>
                        </div>
                        <button class="pin-like-btn ${isLiked ? 'is-liked' : ''}" data-action="like" data-pin-id="${pin.id}" aria-label="Like pin">
                            <svg viewBox="0 0 24 24" width="16" height="16" class="heart-icon" fill="${isLiked ? '#E60023' : 'none'}" stroke="${isLiked ? '#E60023' : 'currentColor'}" stroke-width="2"><path d="M19 14c1.49-1.46 3-3.21 3-5.5A5.5 5.5 0 0 0 16.5 3c-1.76 0-3 .5-4.5 2-1.5-1.5-2.74-2-4.5-2A5.5 5.5 0 0 0 2 8.5c0 2.3 1.5 4.05 3 5.5l7 7Z"/></svg>
                            <span class="like-count">${pin.likes || 0}</span>
                        </button>
                    </div>
                </div>
            </div>
        `;
    }

    /**
     * Fallback for broken image URLs
     */
    static handleImageError(img) {
        img.onerror = null;
        img.src = 'data:image/svg+xml;utf8,<svg xmlns="http://www.w3.org/2000/svg" width="600" height="400" viewBox="0 0 600 400" fill="%23f0f0f4"><rect width="600" height="400" fill="%23f3f4f6"/><text x="50%" y="48%" dominant-baseline="middle" text-anchor="middle" fill="%239ca3af" font-family="sans-serif" font-size="16" font-weight="600">Image not available</text><text x="50%" y="54%" dominant-baseline="middle" text-anchor="middle" fill="%23d1d5db" font-family="sans-serif" font-size="12">Pixora Inspiration</text></svg>';
    }

    /**
     * Attach events to pins
     */
    static attachEventListeners() {
        if (!this.container) return;

        const cards = this.container.querySelectorAll('.pin-card');
        cards.forEach(card => {
            const pinId = card.getAttribute('data-pin-id');

            // Click on whole card opens modal (unless child clicked an interactive action)
            card.addEventListener('click', (e) => {
                const actionBtn = e.target.closest('[data-action]');
                if (actionBtn) {
                    const action = actionBtn.getAttribute('data-action');
                    this.handleAction(action, pinId, actionBtn, e);
                    return;
                }
                // Open pin detail modal
                PinModal.open(pinId);
            });

            // Keyboard accessibility
            card.addEventListener('keydown', (e) => {
                if (e.key === 'Enter') {
                    PinModal.open(pinId);
                }
            });
        });
    }

    /**
     * Handle quick actions from pin cards
     */
    static handleAction(action, pinId, btnElement, event) {
        event.stopPropagation();
        const pin = StorageManager.getPinById(pinId);
        if (!pin) return;

        switch (action) {
            case 'save': {
                const isSaved = StorageManager.toggleSavePin(pinId);
                btnElement.textContent = isSaved ? 'Saved' : 'Save';
                btnElement.className = `pin-action-btn ${isSaved ? 'pin-btn-saved' : 'pin-btn-save'}`;
                
                if (isSaved) {
                    ToastService.save(`Saved to "${pin.board || 'Profile'}"`, {
                        label: 'View',
                        onClick: () => PixoraApp.navigateTo('saved')
                    });
                } else {
                    ToastService.info('Removed from saved pins');
                }
                // Update profile count badge if present
                PixoraApp.syncCounters();
                break;
            }

            case 'like': {
                const result = StorageManager.toggleLikePin(pinId);
                const countSpan = btnElement.querySelector('.like-count');
                const heartSvg = btnElement.querySelector('.heart-icon');

                if (countSpan) countSpan.textContent = result.likesCount;
                if (result.isLiked) {
                    btnElement.classList.add('is-liked');
                    heartSvg.setAttribute('fill', '#E60023');
                    heartSvg.setAttribute('stroke', '#E60023');
                    ToastService.heart('Liked pin');
                } else {
                    btnElement.classList.remove('is-liked');
                    heartSvg.setAttribute('fill', 'none');
                    heartSvg.setAttribute('stroke', 'currentColor');
                }
                break;
            }

            case 'share': {
                const dummyUrl = `${window.location.origin}${window.location.pathname}#pin=${pinId}`;
                if (navigator.clipboard) {
                    navigator.clipboard.writeText(dummyUrl).then(() => {
                        ToastService.success('Pin link copied to clipboard!');
                    }).catch(() => {
                        ToastService.info('Link ready to share!');
                    });
                } else {
                    ToastService.info('Link ready to share!');
                }
                break;
            }

            case 'download': {
                ToastService.info('Preparing image download...');
                this.downloadImage(pin.imageUrl, `${pin.title.toLowerCase().replace(/[^a-z0-9]/g, '-')}.jpg`);
                break;
            }

            case 'link': {
                // Handled natively by <a> tag href
                break;
            }
        }
    }

    /**
     * Trigger client download of image
     */
    static downloadImage(url, filename) {
        fetch(url, { mode: 'cors' })
            .then(res => res.blob())
            .then(blob => {
                const blobUrl = window.URL.createObjectURL(blob);
                const a = document.createElement('a');
                a.style.display = 'none';
                a.href = blobUrl;
                a.download = filename;
                document.body.appendChild(a);
                a.click();
                window.URL.revokeObjectURL(blobUrl);
                document.body.removeChild(a);
                ToastService.success('Download started!');
            })
            .catch(() => {
                // Cross-origin fallback: open image in new tab
                window.open(url, '_blank');
                ToastService.info('Opened image in a new tab for download.');
            });
    }

    /**
     * Show loading skeleton cards
     */
    static showSkeletons(count = 10) {
        if (!this.container) this.init();
        if (!this.container) return;

        const heights = [320, 440, 500, 380, 480, 420, 560, 360, 460, 520];
        let skeletons = '';
        for (let i = 0; i < count; i++) {
            const h = heights[i % heights.length];
            sketons += `
                <div class="pin-card skeleton-card">
                    <div class="skeleton-media" style="height: ${h}px;"></div>
                    <div class="skeleton-text skeleton-title"></div>
                    <div class="skeleton-row">
                        <div class="skeleton-avatar"></div>
                        <div class="skeleton-text skeleton-sub"></div>
                    </div>
                </div>
            `;
        }
        this.container.innerHTML = skeletons;
    }
}
