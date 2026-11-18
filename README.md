# Member 10: Data Architecture, Asset Curation & Application Integration

## 👤 Member Information
- **Name / Assignee:** Member 10
- **Module Name:** Mock Database Schema, Asset Curation & App Integration
- **Primary Source Files:** `frontend/js/data.js`, `frontend/js/app.js`

---

## 🎯 Contribution Overview
Member 10 established the informational architecture, visual media curation, and top-level application lifecycle for **PIXORA**:
1. **Curated High-Resolution Asset Database**:
   - Curated 18+ high-definition photographs from Unsplash with optimized compression and varied heights (380px to 610px) to showcase the authentic Pinterest staggered masonry effect.
   - Categorized across 10 distinct creative disciplines: Architecture, Art & Design, Nature, Photography, Fashion, Technology, Interior Decor, Culinary Art, Travel, and Minimalism.
2. **Schema & Model Definitions**:
   - Designed normalized JSON schemas for Pins, Boards, Users, Comments, and Collections.
   - Built realistic social activity data: comments with commenter avatars, like counts, and verified creator accounts.
3. **Master Application Integration (`PixoraApp`)**:
   - Orchestrates the initialization lifecycle across all 10 member modules in `DOMContentLoaded`.
   - Coordinates multi-view switches between Home, Explore, Create, Saved, and Profile.
   - Implements `syncCounters()` to keep user avatars, saved pin badges, and follower tallies synchronized across the header, sidebar, and profile tabs.
4. **Curated Explore View**:
   - Designed the Explore Page experience featuring trending banners ("Nordic Architecture", "Minimalist Desks", "Autumn Streetwear") and a global popular pins feed.

---

## 💻 Key Methods & Implementation Details
- `PixoraApp.init()`: Boots storage, registers modal listeners, sets up explore view, and renders initial masonry feed.
- `PixoraApp.navigateTo(viewName, updateHash)`: Central dispatcher coordinating view visibility and data refreshes.
- `PixoraApp.syncCounters()`: Updates header avatar and badge counters dynamically across desktop and mobile navigation bars.
- `PixoraApp.renderExploreView()`: Generates the curated editorial Explore page.
- `INITIAL_PINS`, `INITIAL_BOARDS`, `INITIAL_CATEGORIES`, `INITIAL_PROFILE`: Structured baseline data definitions.

---

## 🧪 How to Test This Module
1. Launch the app in any browser: verify that 18+ stunning pins load immediately with varied heights without any blank gaps.
2. Click the **Explore** navigation tab: verify the trending visual banners load with topic titles and follower counts.
3. Open browser console (`F12`): notice the branded Pixora startup banner indicating clean module integration.
4. Verify that pin data includes author names, handles, verification badges, and realistic discussion comments.

---

## 🎓 Viva / Presentation Q&A Preparation
- **Q1: What data structure did you choose to represent a Pin?**  
  *Answer:* An object schema containing: `id`, `title`, `description`, `imageUrl`, `aspectRatio`, `category`, `board`, `tags` (array), `sourceUrl`, `likes` (number), `saves` (number), `isLiked` (boolean), `isSaved` (boolean), nested `author` object (name, handle, avatar, verified), and nested `comments` array.
- **Q2: Why is aspect ratio variation important in a Pinterest clone?**  
  *Answer:* Uniform rectangular or square cards would look like a basic e-commerce grid. Varying aspect ratios (tall, medium, ultra-tall) allow cards to fill vertical voids organically, creating the signature fluid Pinterest masonry experience.
- **Q3: How does `PixoraApp` coordinate the different team modules?**  
  *Answer:* `PixoraApp` acts as the Master Controller (Mediator pattern). It initializes `StorageManager`, binds `MasonryFeed`, `PinModal`, `PinCreator`, and `ProfileManager`, and routes view changes while keeping shared UI states (like unread badges and saved counters) perfectly in sync.
