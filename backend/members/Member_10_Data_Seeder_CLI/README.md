# Member 10: Mock Data Seeder, CLI Terminal Menu & App Integration

## 👤 Member Information
- **Name / Assignee:** Member 10
- **Role:** Data Seeding, Interactive Terminal CLI & Application Integration
- **Files Owned:** `DataSeeder.hpp`, `DataSeeder.cpp`, `CLI.hpp`, `CLI.cpp`, `main.cpp`
- **Core Technology:** C++17, Terminal I/O (`<iostream>`), System Architecture

---

## 🎯 Contribution Overview
Member 10 established the initial media dataset, the interactive **Console CLI Menu**, and the master entry point (`main.cpp`):
1. **Curated High-Res C++ Dataset (`DataSeeder`)**:
   - Hardcoded, realistic initial dataset of 10+ high-definition Unsplash pins across Architecture, Tech, Fashion, Interiors, Nature, and Photography.
   - Initial board definitions ("Dream Architecture", "Minimalist Workspaces", "Alpine Wanderlust") and user profile configuration.
2. **Interactive Terminal CLI (`CLI`)**:
   - Menu-driven console interface where students and professors can interact with all platform capabilities without opening a browser:
     - `[1] View Pins Feed`
     - `[2] Search Pins`
     - `[3] Create a New Pin`
     - `[4] Like / Save a Pin`
     - `[5] View User Profile`
     - `[6] View Boards & Collections`
     - `[7] View Recent Activity Notifications`
     - `[8] Save State to Disk`
3. **Master Bootstrap (`main.cpp`)**:
   - Orchestrates all 10 member components on startup.
   - Supports execution flags:
     - `./pixora --server [port]`: Starts the C++ Web Server.
     - `./pixora --cli`: Launches the Terminal CLI.
     - `./pixora --both`: Spawns C++ web server in background and launches the terminal CLI simultaneously!

---

## 💻 Key Methods
- `DataSeeder::getInitialPins()`
- `DataSeeder::getInitialBoards()`
- `DataSeeder::getInitialProfile()`
- `CLI::run()`
- `main(int argc, char* argv[])`

---

## 🎓 C++ Viva / Oral Exam Questions & Answers
- **Q1: How does `main.cpp` coordinate the 10 member modules?**  
  *Answer:* `main.cpp` acts as the system orchestrator. It instantiates `DatabaseManager` (Member 07), seeds data via `DataSeeder` (Member 10), passes state to `FeedManager` (Member 02) and `Profile` (Member 05), wires up `InteractionManager` (Member 03), `PinCreator` (Member 04), and `NotificationService` (Member 08), and passes these into `HttpServer` (Member 01) or `CLI` (Member 10).
- **Q2: How does `./pixora --both` run both the web server and the terminal menu?**  
  *Answer:* It uses C++11 `<thread>` to launch `HttpServer::start()` in a separate detached worker thread (`std::thread(...).detach()`), while the main thread continues executing the blocking terminal loop in `CLI::run()`.
- **Q3: How do you prevent input stream errors in interactive terminal applications?**  
  *Answer:* When reading input with `std::cin >> choice`, if non-numeric characters are entered, `std::cin.fail()` is triggered. We call `std::cin.clear()` to reset error flags and read remaining invalid tokens into a dummy string to clear the stream buffer.
