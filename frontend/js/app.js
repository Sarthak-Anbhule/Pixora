/**
 * PIXORA - Master Application Orchestrator
 * Integrates all 10 member modules into a unified, reactive social application.
 */

class PixoraApp {
    static currentView = 'home';

    static init() {
        console.log('%c✨ PIXORA - Inspire. Collect. Create. ✨', 'color: #E60023; font-size: 16px; font-weight: bold;');

        // 1. Storage & State initialization
        StorageManager.init();

        // 2. UI Subsystems
        ToastService.init();
        MasonryFeed.init('pins-masonry-grid');
        PinModal.init();
        PinCreator.init();
        ProfileManager.init();
        SearchFilterEngine.init();
        NavigationController.init();
        AnimationController.init();

        // 3. Setup explore page components
        this.renderExploreView();

        // 4. Initial counter and avatar sync
        this.syncCounters();

        // 5. Render initial feed
        this.refreshCurrentView();

        console.log('Pixora frontend successfully mounted.');
    }

    /**
     * Navigate between application views
     */
    static navigateTo(viewName, updateHash = true) {
        this.currentView = viewName;
        NavigationController.switchView(viewName, updateHash);

        // Perform view-specific renders
        switch (viewName) {
            case 'home':
                SearchFilterEngine.applyFilters();
                break;
            case 'explore':
                this.renderExploreView();
                break;
            case 'create':
                PinCreator.setupBoardSelector();
                break;
            case 'saved':
                this.renderSavedView();
                break;
            case 'profile':
                ProfileManager.renderProfileHeader();
                ProfileManager.renderTabContent();
                break;
        }

        this.syncCounters();
        AnimationController.setupIntersectionObserver();
    }

    /**
     * Refresh the currently displayed view
     */
    static refreshCurrentView() {
        this.navigateTo(this.currentView, false);
    }

    /**
     * Render the Explore page with trending topics and visual collections
     */
    static renderExploreView() {
        const container = document.getElementById('explore-featured-container');
        if (!container) return;

        const exploreCollections = [
            {
                title: 'Nordic Architecture & Light',
                tag: 'architecture',
                image: 'https://images.unsplash.com/photo-1600585154340-be6161a56a0c?auto=format&fit=crop&w=800&q=80',
                count: '3.4k Pins'
            },
            {
                title: 'Minimalist Desk Setup Inspo',
                tag: 'tech',
                image: 'https://images.unsplash.com/photo-1518455027359-f3f8164ba6bd?auto=format&fit=crop&w=800&q=80',
                count: '2.1k Pins'
            },
            {
                title: 'Autumn Editorial Streetwear',
                tag: 'fashion',
                image: 'https://images.unsplash.com/photo-1515886657613-9f3515b0c78f?auto=format&fit=crop&w=800&q=80',
                count: '1.9k Pins'
            },
            {
                title: 'Serene Alpine Horizons',
                tag: 'nature',
                image: 'https://images.unsplash.com/photo-1506744038136-46273834b3fb?auto=format&fit=crop&w=800&q=80',
                count: '4.8k Pins'
            }
        ];

        container.innerHTML = `
            <div class="explore-hero-banner">
                <span class="explore-pill-tag">✨ Trending Right Now</span>
                <h2 class="explore-hero-title">Discover fresh perspectives and curated collections</h2>
                <p class="explore-hero-subtitle">Hand-picked visual inspiration across art, architecture, lifestyle, and design.</p>
            </div>

            <div class="explore-curated-grid">
                ${exploreCollections.map(c => `
                    <div class="explore-banner-card" onclick="SearchFilterEngine.setCategory('${c.tag}')">
                        <img src="${c.image}" alt="${c.title}" class="explore-banner-img" />
                        <div class="explore-card-overlay">
                            <span class="explore-card-count">${c.count}</span>
                            <h3 class="explore-card-title">${c.title}</h3>
                            <span class="explore-explore-btn">Explore topic &rarr;</span>
                        </div>
                    </div>
                `).join('')}
            </div>

            <div class="explore-feed-section">
                <div class="explore-section-header">
                    <h3 class="explore-section-heading">Popular Pins Worldwide</h3>
                </div>
                <div class="pins-grid-layout" id="explore-pins-grid"></div>
            </div>
        `;

        // Render popular pins in explore
        const allPins = StorageManager.getPins().slice(0, 14);
        MasonryFeed.container = document.getElementById('explore-pins-grid');
        MasonryFeed.renderPins(allPins);
    }

    /**
     * Render the dedicated Saved Pins View
     */
    static renderSavedView() {
        const savedPins = StorageManager.getSavedPins();
        MasonryFeed.container = document.getElementById('saved-pins-grid');
        MasonryFeed.renderPins(savedPins, "You haven't saved any pins yet. Explore the feed and tap 'Save' to collect them here!");
    }

    /**
     * Synchronize all counters, badge numbers and header user info
     */
    static syncCounters() {
        const profile = StorageManager.getProfile();
        const savedCount = StorageManager.getSavedPinIds().length;

        // Header user avatar
        const headerAvatar = document.querySelector('.header-avatar-img');
        if (headerAvatar) {
            headerAvatar.src = profile.avatar;
            headerAvatar.alt = profile.name;
        }

        // Saved badge in sidebar / bottom nav
        const savedBadges = document.querySelectorAll('.nav-saved-badge');
        savedBadges.forEach(b => {
            b.textContent = savedCount;
            b.style.display = savedCount > 0 ? 'inline-block' : 'none';
        });

        // Profile stats
        const savesStat = document.getElementById('profile-saves-stat');
        if (savesStat) savesStat.textContent = savedCount;

        const followersStat = document.getElementById('profile-followers-stat');
        if (followersStat) followersStat.textContent = (profile.followersCount || 1840).toLocaleString();

        const followingStat = document.getElementById('profile-following-stat');
        if (followingStat) followingStat.textContent = profile.followingCount || 392;
    }
}

// Global bootstrap
document.addEventListener('DOMContentLoaded', () => {
    PixoraApp.init();
});
