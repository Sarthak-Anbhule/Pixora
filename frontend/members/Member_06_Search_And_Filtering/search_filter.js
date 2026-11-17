/**
 * PIXORA - Member 06 Contribution Module
 * Subsystem: Search Engine & Category Filtering Architecture
 * 
 * Responsibilities:
 * - Omnibox search input handling with debounced event listener.
 * - Multi-field search algorithm (matching title, description, category, author, board, tags).
 * - Horizontal category pills navigation bar with active highlighting.
 * - Unified combination filter (Search Query + Active Category).
 * - Clear search button toggle and smooth auto-scrolling for pills.
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

        const pills = this.categoryContainer.querySelectorAll('.category-pill');
        pills.forEach(pill => {
            pill.addEventListener('click', () => {
                const catId = pill.getAttribute('data-category-id');
                this.setCategory(catId);
            });
        });
    }

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

        if (PixoraApp.currentView !== 'home') {
            PixoraApp.navigateTo('home');
        }

        this.applyFilters();
    }

    static applyFilters() {
        const allPins = StorageManager.getPins();
        const q = this.currentQuery.toLowerCase();
        const cat = this.activeCategory;

        const filtered = allPins.filter(pin => {
            const matchesCategory = (cat === 'all' || pin.category === cat || (pin.tags && pin.tags.includes(cat)));

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
