# ✨ PIXORA — Premium Pinterest-Inspired Social Media Platform

> **Inspire. Collect. Create.**  
> A production-grade visual discovery and social pinning platform built with vanilla HTML5, CSS3, and ES6+ JavaScript, architected collaboratively across a 10-member development team.

---

## 🌟 Key Features

- **Pinterest-Style Responsive Masonry Feed**: Dynamic CSS multi-column staggered image layout (5 columns on desktop down to 2 columns on mobile devices) with lazy loading and broken-image fallbacks.
- **Card Hover Overlays**: Quick Red "Save" / "Saved" button, direct source link badges, one-click image download with Blob processing, and link copy sharing.
- **Pin Detail Modal**: High-res split-screen modal view featuring board saving selector, interactive discussion thread with emojis, author verification badge, follower count, and "More to Explore" recommendations.
- **Pin Creation Studio**: Drag-and-drop file upload using HTML5 FileReader (Base64 encoding), direct image URL preview, inline board creator, category dropdown, and tag parsing.
- **User Profile & Boards**: Custom landscape cover banner, avatar, bio, live counters (Followers, Following, Saves), Edit Profile modal, and board collections with board-specific pin filtering.
- **Omnibox Search & Category Filters**: Multi-field real-time search with input debounce, paired with horizontally scrollable category filter pills.
- **State Persistence with LocalStorage**: Saves, likes, custom pins, boards, comments, and profile edits persist in the browser across page reloads.
- **Dark & Light Mode**: Complete theme engine with CSS Custom Properties and preference persistence.
- **Toast Notifications System**: Stacked, animated micro-feedback alerts with functional action buttons.
- **10-Member Group Distribution**: Cleanly separated contribution modules and documentation inside `members/`.

---

## 📁 Project Structure

```
PIXORA/
├── frontend/
│   ├── index.html                       # Main Application Single-Page Entry
│   ├── css/
│   │   ├── main.css                     # Global variables, typography, reset, dark theme
│   │   ├── navigation.css               # Sidebar, sticky header, mobile bottom nav
│   │   ├── masonry.css                  # Multi-column grid, pin cards, skeleton shimmer
│   │   ├── modal.css                    # Pin detail split modal, comments, related pins
│   │   ├── create.css                   # Pin creator studio, drag & drop, form fields
│   │   ├── profile.css                  # Profile banner, avatar, tabs, boards layout
│   │   └── components.css               # Category chips, toast alerts, explore page
│   ├── js/
│   │   ├── data.js                      # Initial high-res Unsplash dataset & schemas (Member 10)
│   │   ├── storage.js                   # LocalStorage persistence & state manager (Member 07)
│   │   ├── notifications.js             # Toast notification engine (Member 08)
│   │   ├── masonry.js                   # Masonry grid & card renderer (Member 02)
│   │   ├── modal.js                     # Pin detail modal & social features (Member 03)
│   │   ├── create.js                    # Pin creator studio & file reader (Member 04)
│   │   ├── profile.js                   # User profile, tabs & board collections (Member 05)
│   │   ├── search.js                    # Omnibox search & category filters (Member 06)
│   │   ├── navigation.js                # SPA routing & layout controller (Member 01)
│   │   ├── animations.js                # Theme toggle, ripples, viewport observer (Member 09)
│   │   └── app.js                       # Master bootstrap & orchestration (PixoraApp)
│   ├── members/                         # 10 Dedicated Member Contribution Folders
│   │   ├── Member_01_Navigation_Layout/
│   │   ├── Member_02_Masonry_Grid_Engine/
│   │   ├── Member_03_Pin_Detail_Modal/
│   │   ├── Member_04_Pin_Creator_Studio/
│   │   ├── Member_05_Profile_And_Boards/
│   │   ├── Member_06_Search_And_Filtering/
│   │   ├── Member_07_Storage_And_State_Persistence/
│   │   ├── Member_08_Notifications_And_Feedback/
│   │   ├── Member_09_Responsive_And_Animations/
│   │   └── Member_10_Data_Assets_And_Integration/
│   ├── TEAM_DISTRIBUTION_GUIDE.md       # Master 10-member roster, roles & viva prep
│   └── README.md                        # Frontend documentation
└── README.md                            # Project root documentation
```

---

## ⚡ How to Run Locally

You can run **PIXORA** instantly with any standard web browser. No complex package installation, build steps, or server frameworks required!

### Option 1: Using Python (Recommended)
Open your terminal in the `PIXORA` directory and run:

```bash
cd frontend
python3 -m http.server 8000
```
Then open your browser and navigate to:
**`http://localhost:8000`**

### Option 2: Using VS Code Live Server
1. Open the `PIXORA` folder in Visual Studio Code.
2. Install the **Live Server** extension (by Ritwick Dey).
3. Right-click on `frontend/index.html` and select **"Open with Live Server"**.

### Option 3: Using Node.js (npx)
```bash
npx serve frontend
```

### Option 4: Direct File Opening
You can also directly double-click or open `frontend/index.html` in Chrome, Safari, Firefox, or Edge.

---

## 👥 10-Member Group Distribution
For college presentations, grading, and team sharing, refer to:
👉 **[`frontend/TEAM_DISTRIBUTION_GUIDE.md`](./frontend/TEAM_DISTRIBUTION_GUIDE.md)**

Inside `frontend/members/`, each member has their own dedicated folder with:
- Their component code file
- A comprehensive `README.md` explaining their role, code walkthrough, testing instructions, and viva/oral exam questions with model answers.
