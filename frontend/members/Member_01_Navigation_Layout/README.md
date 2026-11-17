# Member 01: Navigation Shell & Application Routing

## 👤 Member Information
- **Name / Assignee:** Member 01
- **Module Name:** Navigation Controller & Application Shell
- **Primary Source Files:** `frontend/js/navigation.js`, `frontend/css/navigation.css`

---

## 🎯 Contribution Overview
Member 01 was responsible for designing and implementing the core Single-Page Application (SPA) routing and navigation system of **PIXORA**. This includes:
1. Building the **Fixed Desktop Sidebar** with active state indicators and tooltips.
2. Managing **view transitions** between:
   - `home`: Masonry feed with category pills
   - `explore`: Curated collections and trends
   - `create`: Pin Creator studio
   - `saved`: User's saved pins collection
   - `profile`: User profile, boards, and statistics
3. Synchronizing browser URL hash routing (`#home`, `#explore`, `#pin=pin-1`) so users can bookmark or share direct links, and browser back/forward buttons work naturally via `window.addEventListener('popstate')`.
4. Implementing the **Settings Modal** and "Reset Demo Data" option.

---

## 💻 Key Methods & Implementation Details
- `NavigationController.init()`: Binds click handlers to sidebar and header navigation items and reads initial URL hash.
- `NavigationController.switchView(viewName, updateHash)`: Toggles visibility classes (`hidden-view` vs `active-view`), updates active navigation button styles, and updates `window.location.hash`.
- `NavigationController.handleInitialRoute()`: Parses deep links (such as `#pin=pin-2` or `#profile`) on page load.
- `NavigationController.setupSettingsModal()`: Handles modal open/close and triggers `StorageManager.resetToDefaults()`.

---

## 🧪 How to Test This Module
1. Click between sidebar buttons: **Home**, **Explore**, **Create**, **Saved**, **Profile**. Notice instantaneous view switching with smooth fade-in animations.
2. Look at your browser address bar: notice `#home`, `#explore`, `#create` updating automatically.
3. Click your browser's **Back** and **Forward** buttons: verify that views switch accordingly.
4. Click the gear icon at the bottom of the sidebar to test the Settings and Demo Data Reset modal.

---

## 🎓 Viva / Presentation Q&A Preparation
- **Q1: How does your Single Page App (SPA) navigate without refreshing the page?**  
  *Answer:* By capturing navigation click events with `e.preventDefault()`, toggling CSS classes (`hidden-view` / `active-view`) on view section containers, and updating the browser URL using `window.location.hash`.
- **Q2: How do you handle browser back and forward buttons?**  
  *Answer:* By listening to the `popstate` window event, which detects when the user clicks the browser back or forward arrows, extracting the target hash, and calling `switchView`.
- **Q3: How is the sidebar layout made responsive?**  
  *Answer:* On desktop screens (width > 768px), the sidebar is fixed at 80px width (`position: fixed`). On smaller mobile devices (<= 768px), media queries hide the sidebar and activate the bottom navigation bar (`pixora-bottom-nav`).
