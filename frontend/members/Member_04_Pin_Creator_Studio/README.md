# Member 04: Pin Creation Studio & Media Ingestion

## 👤 Member Information
- **Name / Assignee:** Sarthak Anbhule (Member 04)
- **Module Name:** Pin Creation Studio & Media Processor
- **Primary Source Files:** `frontend/js/create.js`, `frontend/css/create.css`

---

## 🎯 Contribution Overview
Member 04 authored the content generation engine of **PIXORA**: the **Pin Creator Studio**. This module allows users to craft and publish new pins with full control over images, metadata, boards, and categorization:
1. **Interactive Media Ingestion**:
   - Drag & Drop zone supporting image files from desktop with visual drop highlights.
   - HTML5 `FileReader` API integration converting uploaded local images into standard base64 Data URLs so images persist cleanly in `localStorage` without requiring a remote server upload.
   - Remote Image URL loader with client-side image existence validation.
   - Quick one-click curated sample images for fast demo testing.
2. **Metadata & Form Controls**:
   - Title input with character validation.
   - Description textarea for rich captions and notes.
   - Destination website link input.
   - Category picker (Architecture, Fashion, Tech, Art, Nature, Food, etc.).
   - Comma-separated tag parsing (`#minimalism`, `#design`).
3. **Inline Board Creation**:
   - Board selector dynamically reflects all existing user boards.
   - Inline `+ New Board` toggle allows users to create a new board immediately without abandoning their current pin creation draft!
4. **Validation & Toast Integration**:
   - Prevents empty submissions and alerts the user with animated warning toasts.
   - On publish, stores the pin in `StorageManager`, refreshes the feed, and provides a toast with a direct "View Pin" action button.

---

## 💻 Key Methods & Implementation Details
- `PinCreator.setupMediaInputs()`: Configures `dragenter`, `dragover`, `dragleave`, `drop`, and `change` events on the dropzone.
- `PinCreator.handleLocalFile(file)`: Validates file mime type and size, then invokes `FileReader.readAsDataURL()`.
- `PinCreator.handleImageUrl(url)`: Uses `new Image()` preloading to confirm image availability before rendering preview.
- `PinCreator.setPreview(src)`: Switches dropzone from empty placeholder to active image preview with a remove (X) button.
- `PinCreator.setupBoardSelector()`: Synchronizes board options and provides inline creation mechanics.
- `PinCreator.setupFormSubmission()`: Validates inputs, formats tags, calls `StorageManager.createPin()`, and navigates user to the feed.

---

## 🧪 How to Test This Module
1. Navigate to the **Create** view via the sidebar (+ icon).
2. Click any of the "Quick samples" buttons (e.g. "Skyscraper"): verify the image preview immediately appears inside the dropzone.
3. Or drag an image file from your computer onto the dropzone: verify it loads instantly.
4. Enter a title (e.g., "Nordic Loft Design") and description.
5. Click **+ New Board**, type "My Studio Inspo", and click **Save**: notice the new board is selected automatically.
6. Click **Publish Pin**: verify the success toast appears and your new pin is now the very first card on the Home Feed!

---

## 🎓 Viva / Presentation Q&A Preparation
- **Q1: How do you save images uploaded from the user's computer without a backend server?**  
  *Answer:* By reading the file into memory with JavaScript's `FileReader` API using `readAsDataURL()`. This encodes the image into a Base64 string that can be saved directly into `localStorage`.
- **Q2: How does the drag-and-drop feature work?**  
  *Answer:* We listen to HTML5 drag events (`dragover`, `dragleave`, `drop`) on the dropzone element, call `e.preventDefault()` to stop the browser from opening the file in a new tab, and access `e.dataTransfer.files[0]`.
- **Q3: How do you handle tags entered with commas and hashtags?**  
  *Answer:* We split the string by commas (`split(',')`), strip leading `#` symbols (`replace(/^#/, '')`), trim whitespace, and filter out empty tokens.
