# Member 05: User Profile & Board Collections Management

## 👤 Member Information
- **Name / Assignee:** Member 05
- **Module Name:** User Profile & Board Collections Architecture
- **Primary Source Files:** `frontend/js/profile.js`, `frontend/css/profile.css`

---

## 🎯 Contribution Overview
Member 05 built the personal portfolio and curation engine of **PIXORA**:
1. **Aesthetic Profile Header**:
   - High-resolution landscape cover banner with gradient backdrop.
   - Prominent profile avatar with verified badge.
   - Full display name, handle (`@elenavance`), rich bio, location, and verified external website link.
   - Live synchronization for statistics: Followers, Following, and Saved Pin counts.
2. **Tabbed Content Architecture**:
   - **Saved Pins**: Renders all pins the user has bookmarked across the platform.
   - **Created Pins**: Isolates and displays pins authored directly by the current user.
   - **Boards**: Displays customized collections (e.g. "Dream Architecture", "Minimalist Workspaces") with cover photos, secret board badges, and live pin counts.
3. **Board Drill-Down Experience**:
   - Clicking any board card smoothly navigates into that specific board's curated pins, with a breadcrumb button to return back to All Boards.
4. **Edit Profile & Create Board Modals**:
   - Edit Profile dialog allows instant customization of name, bio, location, website, and avatar image.
   - Create Board modal enables instant board generation with secret/public toggles.

---

## 💻 Key Methods & Implementation Details
- `ProfileManager.renderProfileHeader()`: Hydrates user details and binds edit/share actions.
- `ProfileManager.setupTabListeners()`: Manages switching between Saved, Created, and Boards tabs.
- `ProfileManager.renderBoardsList(container)`: Loops through boards in storage, dynamically calculating how many saved pins belong to each board.
- `ProfileManager.renderBoardSpecificPins(container)`: Filters pins by `pin.board === activeBoardFilter` and renders dedicated masonry view.
- `ProfileManager.setupEditProfileModal()`: Validates and persists edited user profile data via `StorageManager.updateProfile()`.
- `ProfileManager.setupCreateBoardModal()`: Handles creation of new boards.

---

## 🧪 How to Test This Module
1. Navigate to the **Profile** view via the sidebar or top header avatar.
2. Verify that follower counts, following counts, and saved counts match reality.
3. Click on the **Boards** tab: notice the rich board collection cards with dynamic pin counts.
4. Click on **"Dream Architecture"**: verify you drill into that collection and see only pins saved to that board.
5. Click **"All Boards"** to navigate back.
6. Click **Edit Profile**, change your display name or bio, and click **Save Changes**: verify the header updates immediately without page reload!

---

## 🎓 Viva / Presentation Q&A Preparation
- **Q1: How do you dynamically compute pin counts for each board?**  
  *Answer:* In `renderBoardsList()`, we query all pins using `StorageManager.getPins()` and count how many have `p.board === board.title` and `p.isSaved === true`.
- **Q2: How does the Board drill-down navigation work?**  
  *Answer:* When a board card is clicked, we store the board title in `ProfileManager.activeBoardFilter` and re-render the tab content, filtering `getPins()` for only pins matching that board title.
- **Q3: How are profile updates reflected across the application?**  
  *Answer:* `StorageManager.updateProfile()` saves the updated profile object in `localStorage`. Then `ProfileManager.renderProfileHeader()` and `PixoraApp.syncCounters()` are called, instantly updating the header avatar, profile text, and badge counters.
