# ✨ PIXORA — Premium Pinterest-Inspired Social Media Platform

> **Inspire. Collect. Create.**  
> A full-stack visual discovery and social pinning platform featuring a modern **Pinterest-style frontend** and a high-performance **C++17 HTTP REST API Server & Console Engine**, architected collaboratively across **10 group members** for First Year B.Tech Engineering.

---

## 🌟 Key Features

- **Pinterest-Style Responsive Masonry Feed**: Dynamic CSS multi-column staggered image layout (5 columns on desktop down to 2 columns on mobile devices) with lazy loading and broken-image fallbacks.
- **Card Hover Overlays**: Quick Red "Save" / dark "Saved" toggle, source website badge, one-click image download with Blob processing, and link copy sharing.
- **Pin Detail Modal**: High-res split-screen modal view featuring board saving selector, interactive discussion thread with emojis, author verification badge, follower count, and "More to Explore" recommendations.
- **Pin Creation Studio**: Drag-and-drop file upload using HTML5 FileReader (Base64 encoding), direct image URL preview, inline board creator, category dropdown, and tag parsing.
- **User Profile & Boards**: Custom landscape cover banner, avatar, bio, live counters (Followers, Following, Saves), Edit Profile modal, and board collections with board-specific pin filtering.
- **Omnibox Search & Category Filters**: Multi-field real-time search with input debounce, paired with horizontally scrollable category filter pills.
- **State Persistence**: Dual persistence layer: browser `localStorage` + persistent disk JSON files (`backend/data/pins.json`, `boards.json`, `profile.json`).
- **Dark & Light Mode**: Complete theme engine with CSS Custom Properties and preference persistence.
- **Dual C++ Run Modes**:
  1. **Web Server Mode**: High-performance C++ HTTP socket server serving frontend and REST API on `http://localhost:8080`.
  2. **Interactive Terminal CLI Mode**: Menu-driven console interface for testing all features in the terminal (ideal for college viva).
- **10-Member Group Distribution**: Complete codebase divided into 10 distinct member modules with dedicated documentation, source files, and Viva questions.

---

## 👥 10-Member Team Distribution & Presentation Roster

Each member owns dedicated source modules in both `backend/members/` (C++) and `frontend/members/` (Frontend):

| Member # | Subsystem / Role | Key C++ Files | Frontend Module | Member Folder |
| :---: | :--- | :--- | :--- | :--- |
| **01** | **HTTP Server & App Shell** | `HttpServer.hpp`, `HttpServer.cpp` | `js/navigation.js`, `css/navigation.css` | [`backend/members/Member_01_Server_Controller/`](backend/members/Member_01_Server_Controller/) |
| **02** | **Pin Model & Masonry Feed** | `Pin.hpp`, `Pin.cpp`, `FeedManager.hpp` | `js/masonry.js`, `css/masonry.css` | [`backend/members/Member_02_Pin_Feed_Manager/`](backend/members/Member_02_Pin_Feed_Manager/) |
| **03** | **Pin Detail Modal & Social Feedback** | `InteractionManager.hpp`, `InteractionManager.cpp` | `js/modal.js`, `css/modal.css` | [`backend/members/Member_03_Interaction_Engine/`](backend/members/Member_03_Interaction_Engine/) |
| **04** | **Sarthak Anbhule** | `PinCreator.hpp`, `PinCreator.cpp` | `js/create.js`, `css/create.css` | [`backend/members/Member_04_Pin_Ingestion_Studio/`](backend/members/Member_04_Pin_Ingestion_Studio/) |
| **05** | **User Profile & Board Collections** | `Profile.hpp`, `Profile.cpp`, `Board.hpp` | `js/profile.js`, `css/profile.css` | [`backend/members/Member_05_Profile_And_Boards/`](backend/members/Member_05_Profile_And_Boards/) |
| **06** | **Search Engine & Category Filters** | `SearchEngine.hpp`, `SearchEngine.cpp` | `js/search.js`, `css/components.css` | [`backend/members/Member_06_Search_Filter_Algorithm/`](backend/members/Member_06_Search_Filter_Algorithm/) |
| **07** | **File Persistence & Storage Service** | `DatabaseManager.hpp`, `DatabaseManager.cpp` | `js/storage.js` | [`backend/members/Member_07_File_Persistence_Database/`](backend/members/Member_07_File_Persistence_Database/) |
| **08** | **Toast Notifications & Event Queue** | `NotificationService.hpp`, `NotificationService.cpp`| `js/notifications.js` | [`backend/members/Member_08_Notifications_Analytics/`](backend/members/Member_08_Notifications_Analytics/) |
| **09** | **Micro-Animations, Theming & Utilities** | `Utils.hpp`, `Utils.cpp`, `JsonHelper.hpp` | `js/animations.js`, `css/main.css` | [`backend/members/Member_09_System_Utilities_Json/`](backend/members/Member_09_System_Utilities_Json/) |
| **10** | **Data Seeder, CLI Terminal & Orchestrator**| `DataSeeder.hpp`, `CLI.hpp`, `main.cpp` | `js/data.js`, `js/app.js` | [`backend/members/Member_10_Data_Seeder_CLI/`](backend/members/Member_10_Data_Seeder_CLI/) |

*Detailed presentation and Viva cheatsheets:*
- 👉 **[`backend/CPP_TEAM_DISTRIBUTION_GUIDE.md`](backend/CPP_TEAM_DISTRIBUTION_GUIDE.md)** (C++ Architecture & Viva Prep)
- 👉 **[`frontend/TEAM_DISTRIBUTION_GUIDE.md`](frontend/TEAM_DISTRIBUTION_GUIDE.md)** (Frontend Architecture & Viva Prep)

---

## 🛠️ How to Build and Run

### 1. Compile the C++ Engine
Using the included `Makefile`:
```bash
make
```
*Compiles the native binary `pixora` with `clang++ -std=c++17` (zero external dependencies).*

### 2. Run the C++ Web Server (Default)
```bash
./pixora --server 8080
# Or: make run
```
Then open your browser at **`http://localhost:8080`**.

### 3. Run the Interactive Terminal CLI (College Lab Demo)
```bash
./pixora --cli
# Or: make cli
```
Launches an interactive menu-driven console program in your terminal:
```text
======================================================
  ✨ PIXORA — C++ Engine (Console & Server Edition) ✨
        Designed & Engineered by 10 Group Members       
======================================================

[1] 🖼️  View Pins Feed (10 pins)
[2] 🔍 Search Pins (by title, tag, author, category)
[3] ➕ Create a New Pin
[4] ❤️  Like / 📌 Save a Pin
[5] 👤 View User Profile
[6] 📁 View Boards & Collections
[7] 🔔 View Recent Activity Notifications
[8] 💾 Save State to Disk (backend/data/pins.json)
[0] 🚪 Exit CLI
```

### 4. Run Both Web Server & Terminal Menu
```bash
./pixora --both
# Or: make both
```

---

## 📁 Repository Structure

```
PIXORA/
├── Makefile                             # Master build automation
├── .gitignore                           # Git ignore rules
├── README.md                            # Main project overview
├── backend/                             # C++17 Core Engine & REST Server
│   ├── Makefile                         # Backend build script
│   ├── CPP_TEAM_DISTRIBUTION_GUIDE.md   # C++ 10-member roster & viva guide
│   ├── include/                         # C++ header files (.hpp)
│   ├── src/                             # C++ source files (.cpp)
│   ├── data/                            # Persistent JSON database
│   └── members/                         # 10 Member C++ folders with READMEs
└── frontend/                            # Responsive Web Platform
    ├── index.html                       # SPA HTML entry point
    ├── css/                             # Stylesheets
    ├── js/                              # JavaScript modules
    ├── members/                         # 10 Member Frontend folders with READMEs
    ├── TEAM_DISTRIBUTION_GUIDE.md       # Frontend 10-member roster & viva guide
    └── README.md                        # Frontend documentation
```
