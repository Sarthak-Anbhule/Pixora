# 👥 PIXORA — 10-Member Team Distribution & Project Roster Guide

This document outlines the complete architectural division of **PIXORA** across **10 team members**. Each member has a dedicated folder inside `frontend/members/` containing their specialized module files, code walkthroughs, testing instructions, and viva/oral exam preparation questions.

---

## 📋 Team Roster & Module Breakdown

| Member # | Name (Fill In) | Subsystem / Role | Key Files Owned | Folder Link |
| :---: | :--- | :--- | :--- | :--- |
| **01** | *Member 1* | **Navigation Shell & SPA Routing** | `js/navigation.js`, `css/navigation.css` | [`Member_01_Navigation_Layout/`](./members/Member_01_Navigation_Layout/) |
| **02** | *Member 2* | **Masonry Grid Engine & Pin Rendering** | `js/masonry.js`, `css/masonry.css` | [`Member_02_Masonry_Grid_Engine/`](./members/Member_02_Masonry_Grid_Engine/) |
| **03** | *Member 3* | **Pin Detail Modal & Social Feedback** | `js/modal.js`, `css/modal.css` | [`Member_03_Pin_Detail_Modal/`](./members/Member_03_Pin_Detail_Modal/) |
| **04** | **Sarthak Anbhule** | **Pin Creation Studio & Media Ingestion** | `js/create.js`, `css/create.css` | [`Member_04_Pin_Creator_Studio/`](./members/Member_04_Pin_Creator_Studio/) |
| **05** | *Member 5* | **User Profile & Board Collections** | `js/profile.js`, `css/profile.css` | [`Member_05_Profile_And_Boards/`](./members/Member_05_Profile_And_Boards/) |
| **06** | *Member 6* | **Search Engine & Category Filters** | `js/search.js`, `css/components.css` | [`Member_06_Search_And_Filtering/`](./members/Member_06_Search_And_Filtering/) |
| **07** | *Member 7* | **Storage & State Persistence Layer** | `js/storage.js` | [`Member_07_Storage_And_State_Persistence/`](./members/Member_07_Storage_And_State_Persistence/) |
| **08** | *Member 8* | **Toast Notifications & Interactive Alerts** | `js/notifications.js`, `css/components.css` | [`Member_08_Notifications_And_Feedback/`](./members/Member_08_Notifications_And_Feedback/) |
| **09** | *Member 9* | **Micro-Animations, Theming & Responsiveness**| `js/animations.js`, `css/main.css` | [`Member_09_Responsive_And_Animations/`](./members/Member_09_Responsive_And_Animations/) |
| **10** | *Member 10* | **Data Architecture & App Orchestration** | `js/data.js`, `js/app.js` | [`Member_10_Data_Assets_And_Integration/`](./members/Member_10_Data_Assets_And_Integration/) |

---

## 🔍 Detailed Responsibilities & Viva Q&A by Member

### 🔹 Member 01: Navigation Shell & SPA Routing
- **What they did:** Engineered the SPA routing mechanism, desktop sidebar navigation, header integration, hash-based URL routing (`#home`, `#explore`, `#create`, `#saved`, `#profile`), and the settings modal.
- **Viva Answer to Memorize:** *"I built our client-side routing system using HTML5 and the browser's `hashchange`/`popstate` events. When a user clicks a nav link, our `NavigationController` switches the active view without reloading the page and synchronizes the browser address bar so bookmarks and the browser's back/forward buttons work flawlessly."*

### 🔹 Member 02: Masonry Grid Engine & Pin Rendering
- **What they did:** Implemented the responsive CSS multi-column masonry grid (from 5 columns on desktop down to 2 on mobile), pin card hover overlays, one-click image downloads, and image error fallbacks.
- **Viva Answer to Memorize:** *"I developed the Pinterest masonry feed using CSS Multi-column layout with `column-count` and `break-inside: avoid;`. I also implemented lazy-loading images, an interactive hover overlay with save and download actions, and an SVG error handler for broken URLs."*

### 🔹 Member 03: Pin Detail Modal & Social Feedback
- **What they did:** Created the split-view pin modal, high-resolution media viewer, board save dropdown, comment submission system with emoji helpers, creator follow button, and the 'More to Explore' recommendation engine.
- **Viva Answer to Memorize:** *"I engineered the Pin Detail Modal. It features a split layout with media display on the left and metadata/comments on the right. Users can select which board to save to, leave real-time comments with emojis, follow the author, and discover related pins from the same category."*

### 🔹 Member 04: Pin Creation Studio & Media Ingestion
- **What they did:** Developed the drag-and-drop file upload zone, FileReader Base64 image ingestion, image URL preview loader, inline board creator, and form validation.
- **Viva Answer to Memorize:** *"I built the Pin Creation Studio. I integrated the HTML5 Drag-and-Drop and FileReader APIs to convert local images into base64 Data URLs so users can publish pins without a backend server. I also added an inline board creator so users can create new boards directly during pin creation."*

### 🔹 Member 05: User Profile & Board Collections
- **What they did:** Built the profile header, cover banner, user stats, profile editing modal, and the 3-tab layout (Saved Pins, Created Pins, Boards) with board drill-down filtering.
- **Viva Answer to Memorize:** *"I designed the User Profile and Boards system. It features live statistics (Followers, Following, Saved Pins), an Edit Profile modal, and a collection manager where users can create private/public boards and click on any board to filter and view its specific pins."*

### 🔹 Member 06: Search Engine & Category Filters
- **What they did:** Implemented the header Omnibox search with a 180ms debounce, horizontal category pill navigation, and multi-field search algorithm (matches title, description, category, creator, board, and tags).
- **Viva Answer to Memorize:** *"I built the search and category discovery engine. I implemented a debounced search input to optimize performance and prevent DOM thrashing, and designed a multi-field filter algorithm that matches user queries across titles, tags, categories, and author handles simultaneously."*

### 🔹 Member 07: Storage & State Persistence Layer
- **What they did:** Designed the persistent `localStorage` abstraction layer (`StorageManager`) managing pins, saved IDs, liked IDs, custom boards, and user profile data with memory fallback and data reset capabilities.
- **Viva Answer to Memorize:** *"I authored the State Persistence layer. I designed our centralized `StorageManager` using the browser's `localStorage` API with JSON serialization. It seeds the platform with initial pins on first boot, ensures optimistic state updates for likes/saves, and provides memory resilience if storage is blocked."*

### 🔹 Member 08: Toast Notifications & Interactive Alerts
- **What they did:** Built the animated, non-blocking toast notification stack with context icons, auto-dismiss timers, action buttons (e.g. `[View]` saved pin), and manual close triggers.
- **Viva Answer to Memorize:** *"I created the real-time Toast Notification system. It provides immediate, non-intrusive micro-feedback when users save pins, like content, or encounter validation errors. It includes stacked auto-dismissing cards, custom SVG icons, and interactive action buttons."*

### 🔹 Member 09: Micro-Animations, Theming & Responsiveness
- **What they did:** Implemented dark/light theme switching with CSS variables and storage persistence, button ripple effects, image progressive blur-up, viewport intersection animations, and mobile layout adaptation.
- **Viva Answer to Memorize:** *"I engineered the styling tokens, dark/light theme toggle, and micro-interactions. Using CSS Custom Properties and an `IntersectionObserver`, cards smoothly animate as they enter the viewport. I also ensured full responsiveness with a custom bottom navigation bar on mobile devices."*

### 🔹 Member 10: Data Architecture & App Integration
- **What they did:** Curated 18+ high-resolution Unsplash images across 10 categories with authentic aspect ratios, designed the normalized JSON schemas, built the editorial Explore page, and integrated all modules into `PixoraApp`.
- **Viva Answer to Memorize:** *"I led the data architecture and master application integration. I curated the high-resolution media datasets with staggered aspect ratios to showcase the masonry grid, authored the Explore trends page, and integrated all 10 member modules into a unified reactive application inside `PixoraApp`."*

---

## 🚀 How to Share and Present to Evaluators
1. **Show the Live App:** Open `frontend/index.html` in any browser or launch a local web server (e.g. `python3 -m http.server 8000`).
2. **Demonstrate Team Distribution:** Open the `frontend/members/` folder to show professors the 10 distinct member directories, each containing that member's module code and detailed README report.
3. **Walk Through Each Feature:**
   - Member 01 shows the Sidebar and page routing.
   - Member 02 hovers over cards, shows download and save buttons.
   - Member 03 opens the Pin Detail modal and posts a live comment with emojis.
   - Member 04 uploads an image and publishes a new pin.
   - Member 05 navigates to Profile, clicks on a Board, and edits the profile bio.
   - Member 06 demonstrates instant live search and category chips.
   - Member 07 opens DevTools -> Application -> Local Storage to demonstrate persistence.
   - Member 08 points out the toast alerts and action buttons.
   - Member 09 toggles Dark Mode and shrinks the screen to show the mobile bottom nav.
   - Member 10 explains the data schema and master orchestration.
