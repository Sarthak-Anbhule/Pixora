# Member 02: Masonry Grid Engine & Pin Rendering Architecture

## 👤 Member Information
- **Name / Assignee:** Member 02
- **Module Name:** Masonry Grid & Card Interaction Engine
- **Primary Source Files:** `frontend/js/masonry.js`, `frontend/css/masonry.css`

---

## 🎯 Contribution Overview
Member 02 engineered the defining visual centerpiece of **PIXORA**: the dynamic Pinterest-style Masonry grid and Pin card rendering engine. Key features include:
1. Pure CSS Column Masonry using `column-count`, `column-gap: 16px`, and `break-inside: avoid;` supporting fluid breakpoints (5 columns on ultra-wide screens down to 2 columns on mobile).
2. Pin card construction featuring variable aspect ratio heights, high-resolution media, and progressive lazy loading (`loading="lazy"`).
3. **Card Hover Actions Overlay**:
   - Red **Save** / dark **Saved** toggle button with real-time state change.
   - Destination website badge with parsed hostname domain.
   - One-click image download with Blob URL conversion and CORS fallback.
   - Share / link copy action.
4. Social reactions: Heart like button with live like counter update.
5. Error handling: Graceful SVG fallback for broken image links (`handleImageError`).
6. Pre-loader skeleton shimmer animations for smooth content loading.

---

## 💻 Key Methods & Implementation Details
- `MasonryFeed.init(containerId)`: Stores reference to target grid DOM node.
- `MasonryFeed.renderPins(pins, emptyMessage)`: Converts pins array into cards HTML and binds event handlers.
- `MasonryFeed.createPinCardHtml(pin)`: Generates semantic HTML for a card with author info, like stats, and hover overlay.
- `MasonryFeed.attachEventListeners()`: Uses event delegation to separate general card click (opens modal) from child action buttons (save, like, share, download).
- `MasonryFeed.handleAction(action, pinId, btnElement, event)`: Dispatches save, like, and share events with toast feedback and state sync.
- `MasonryFeed.downloadImage(url, filename)`: Converts image to a local Blob and triggers automatic browser download.

---

## 🧪 How to Test This Module
1. Hover over any pin on the home feed: verify that the dark gradient overlay appears with the Save button, source link, and action buttons.
2. Click the red **Save** button: watch it change to **Saved** immediately with a toast notification and the saved counter badge incrementing.
3. Click the **Heart icon** under the pin: verify the count increments and heart turns red.
4. Click the **Download icon**: verify the image downloads directly to your machine.
5. Resize the browser window from 1920px down to 375px: verify columns adapt smoothly (5 -> 4 -> 3 -> 2 columns).

---

## 🎓 Viva / Presentation Q&A Preparation
- **Q1: How did you implement Pinterest's staggered masonry layout without external libraries?**  
  *Answer:* Using CSS Multi-column layout properties (`column-count: 5`, `column-gap: 16px`) combined with `break-inside: avoid` on the `.pin-card` elements to prevent cards from splitting across columns.
- **Q2: How do you prevent clicking the 'Save' button from also opening the Pin Modal?**  
  *Answer:* By calling `e.stopPropagation()` in the action button handler before checking `e.target.closest('[data-action]')`.
- **Q3: What happens if an image link fails or is broken?**  
  *Answer:* The `onerror` event on the `<img>` triggers `MasonryFeed.handleImageError(this)`, which injects an inline SVG graphic informing the user that the image is unavailable, preventing ugly broken-image icons.
