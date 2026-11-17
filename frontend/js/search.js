/**
 * PIXORA - Search Engine & Category Filtering System
 * Contributed by: Member 06 (Search Algorithm & Category Filter Architecture)
 * 
 * Provides debounced multi-field searching, category pill chips, real-time query
 * suggestions, active state toggles, and seamless combined filtering.
 */

class SearchFilterEngine {
    static activeCategory = 'all';
    static currentQuery = '';
    static searchInput = null;
    static clearSearchBtn = null;
    static categoryContainer = null;
    static debounceTimer = null;

    static init() {
        this.searchInput = document.getElementById('global-search-input');
        this.clearSearchBtn = document.getElementById('clear-search-btn');
        this.categoryContainer = document.getElementById('category-filter-chips');

        this.renderCategoryChips();
        this.setupSearchEvents();
    }

    /**
     * Render category pills
     */
    static renderCategoryChips() {
        if (!this.categoryContainer) return;

        this.categoryContainer.innerHTML = INITIAL_CATEGORIES.map(cat => `
            <button 
                type="button" 
                class="category-pill ${cat.id === this.activeCategory ? 'is-active' : ''}" 
                data-category-id="${cat.id}"
            >
                <span class="pill-title">${cat.name}</span>
            </button>
        `).join('');

        // Attach click listeners to chips
        const pills = this.categoryContainer.querySelectorAll('.category-pill');
        pills.forEach(pill => {
            pill.addEventListener('click', () => {
                const catId = pill.getAttribute('data-category-id');
                this.setCategory(catId);
            });
        });
    }

    /**
     * Setup search bar listeners
     */
    static setupSearchEvents() {
        if (!this.searchInput) return;

        this.searchInput.addEventListener('input', (e) => {
            const val = e.target.value.trim();
            this.currentQuery = val;

            if (this.clearSearchBtn) {
                this.clearSearchBtn.style.display = val ? 'flex' : 'none';
            }

            clearTimeout(this.debounceTimer);
            this.debounceTimer = setTimeout(() => {
                this.applyFilters();
            }, 180);
        });

        if (this.clearSearchBtn) {
            this.clearSearchBtn.addEventListener('click', () => {
                this.searchInput.value = '';
                this.currentQuery = '';
                this.clearSearchBtn.style.display = 'none';
                this.applyFilters();
                this.searchInput.focus();
            });
        }
    }

    /**
     * Switch Category Filter
     */
    static setCategory(categoryId) {
        this.activeCategory = categoryId;
        const pills = this.categoryContainer.querySelectorAll('.category-pill');
        pills.forEach(p => {
            if (p.getAttribute('data-category-id') === categoryId) {
                p.classList.add('is-active');
                p.scrollIntoView({ behavior: 'smooth', block: 'nearest', inline: 'center' });
            } else {
                p.classList.remove('is-active');
            }
        });

        // Ensure we are in home feed
        if (PixoraApp.currentView !== 'home') {
            PixoraApp.navigateTo('home');
        }

        this.applyFilters();
    }

    /**
     * Filter pins based on active category & search query
     */
    static applyFilters() {
        const allPins = StorageManager.getPins();
        const q = this.currentQuery.toLowerCase();
        const cat = this.activeCategory;

        const filtered = allPins.filter(pin => {
            // Category check
            const matchesCategory = (cat === 'all' || pin.category === cat || (pin.tags && pin.tags.includes(cat)));

            // Query check
            if (!q) return matchesCategory;

            const titleMatch = (pin.title || '').toLowerCase().includes(q);
            const descMatch = (pin.description || '').toLowerCase().includes(q);
            const catMatch = (pin.category || '').toLowerCase().includes(q);
            const authorMatch = (pin.author?.name || '').toLowerCase().includes(q) || (pin.author?.handle || '').toLowerCase().includes(q);
            const boardMatch = (pin.board || '').toLowerCase().includes(q);
            const tagMatch = (pin.tags || []).some(t => t.toLowerCase().includes(q));

            const matchesQuery = titleMatch || descMatch || catMatch || authorMatch || boardMatch || tagMatch;
            return matchesCategory && matchesQuery;
        });

        // Render in main masonry
        MasonryFeed.container = document.getElementById('pins-masonry-grid');
        let emptyMsg = 'No pins found';
        if (q && cat !== 'all') {
            emptyMsg = `No pins matching "${q}" in this category.`;
        } else if (q) {
            emptyMsg = `No results found for "${q}".`;
        } else if (cat !== 'all') {
            const catObj = INITIAL_CATEGORIES.find(c => c.id === cat);
            emptyMsg = `No pins found in ${catObj ? catObj.name : cat}.`;
        }

        MasonryFeed.renderPins(filtered, emptyMsg);
    }
}
