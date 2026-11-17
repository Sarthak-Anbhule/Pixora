# Member 06: Search Engine & Category Filter Architecture

## 👤 Member Information
- **Name / Assignee:** Member 06
- **Module Name:** Omnibox Search & Category Filtering Engine
- **Primary Source Files:** `frontend/js/search.js`, `frontend/css/components.css`

---

## 🎯 Contribution Overview
Member 06 engineered the discovery and querying layer of **PIXORA**:
1. **Omnibox Search Bar**:
   - Centered in the top header with search icon and clear button.
   - Real-time debounced input handling (180ms debounce) that prevents performance lag during keystrokes.
   - Clear button (X) automatically toggles on input and resets the query with a single click.
2. **Multi-Field Search Algorithm**:
   - Matches user search terms across 6 distinct fields:
     - `pin.title` (e.g. "Concrete Monolith")
     - `pin.description` (e.g. "Cantilevered residence")
     - `pin.category` (e.g. "architecture")
     - `pin.author.name` or `handle` (e.g. "Kasper Lindqvist")
     - `pin.board` (e.g. "Dream Architecture")
     - `pin.tags` (e.g. "minimalism", "modern", "brutalism")
3. **Horizontal Category Filter Bar**:
   - Smoothly scrollable pill chips: "All Inspiration", "Architecture", "Art & Design", "Nature & Escapes", "Photography", "Fashion & Style", "Tech & Workspaces", "Interior Decor", "Culinary Art", "Travel Guides", "Minimalism".
   - Active state styling with automatic smooth scrolling (`scrollIntoView`) to center the active chip.
4. **Combined Filtering**:
   - Search queries and category pills work concurrently (e.g. filtering for "desk" while the "Tech & Workspaces" category is selected).

---

## 💻 Key Methods & Implementation Details
- `SearchFilterEngine.init()`: Binds search bar inputs and renders initial category chips.
- `SearchFilterEngine.renderCategoryChips()`: Maps `INITIAL_CATEGORIES` into styled HTML button pills.
- `SearchFilterEngine.setupSearchEvents()`: Implements input debounce with `clearTimeout` / `setTimeout`.
- `SearchFilterEngine.setCategory(categoryId)`: Updates active category state and triggers filter recalculation.
- `SearchFilterEngine.applyFilters()`: Executes the multi-field filter predicate over `StorageManager.getPins()` and re-renders the masonry grid.

---

## 🧪 How to Test This Module
1. Click the search input in the header bar and type "desk": verify cards instantly filter to workspace and desk setups.
2. Notice the clear button (X) that appears in the search bar. Click it: verify search input clears and full feed restores.
3. Click the **"Architecture"** category chip: verify only architectural pins are shown and the chip turns active.
4. With "Architecture" selected, search for "concrete": verify it filters specifically for concrete architecture pins.
5. Search for a non-existent phrase (e.g. "xyz123"): verify the styled empty-state illustration appears with advice to explore other categories.

---

## 🎓 Viva / Presentation Q&A Preparation
- **Q1: Why did you implement a debounce mechanism for the search input?**  
  *Answer:* Without debounce, the search function would re-filter and re-render the entire DOM on every single keypress. A 180ms debounce waits until the user pauses typing before executing, making the search fast, smooth, and stutter-free.
- **Q2: Which pin attributes does the search engine match against?**  
  *Answer:* Pin title, description, category, creator name, creator handle, board title, and tags array.
- **Q3: How do category filters interact with search keywords?**  
  *Answer:* They use an `AND` logic combination: a pin must match the selected category condition (`matchesCategory`) AND the text query condition (`matchesQuery`).
