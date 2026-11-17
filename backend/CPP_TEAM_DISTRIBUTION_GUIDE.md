# 👥 PIXORA — 10-Member C++ Engineering Distribution & Viva Guide

This document details the **C++ Object-Oriented Architecture** of **PIXORA**, divided across **10 team members**. Each member owns dedicated C++ class headers (`.hpp`) and implementation files (`.cpp`) inside `backend/members/`, complete with individual documentation and viva preparation questions.

---

## 📋 10-Member C++ Engineering Roster

| Member # | Name (Fill In) | Subsystem / Role | Key C++ Files Owned | Member Folder Link |
| :---: | :--- | :--- | :--- | :--- |
| **01** | *Member 1* | **HTTP Web Server & Socket Engine** | `HttpServer.hpp`, `HttpServer.cpp` | [`backend/members/Member_01_Server_Controller/`](./members/Member_01_Server_Controller/) |
| **02** | *Member 2* | **Pin Model & Feed In-Memory Manager** | `Pin.hpp`, `Pin.cpp`, `FeedManager.hpp`, `FeedManager.cpp` | [`backend/members/Member_02_Pin_Feed_Manager/`](./members/Member_02_Pin_Feed_Manager/) |
| **03** | *Member 3* | **Social Interaction Engine** | `InteractionManager.hpp`, `InteractionManager.cpp` | [`backend/members/Member_03_Interaction_Engine/`](./members/Member_03_Interaction_Engine/) |
| **04** | *Member 4* | **Pin Ingestion Studio & Validation** | `PinCreator.hpp`, `PinCreator.cpp` | [`backend/members/Member_04_Pin_Ingestion_Studio/`](./members/Member_04_Pin_Ingestion_Studio/) |
| **05** | *Member 5* | **User Profile & Board Models** | `Profile.hpp`, `Profile.cpp`, `Board.hpp`, `Board.cpp` | [`backend/members/Member_05_Profile_And_Boards/`](./members/Member_05_Profile_And_Boards/) |
| **06** | *Member 6* | **Search & Relevance Ranking Algorithm**| `SearchEngine.hpp`, `SearchEngine.cpp` | [`backend/members/Member_06_Search_Filter_Algorithm/`](./members/Member_06_Search_Filter_Algorithm/) |
| **07** | *Member 7* | **File Streams & Database Persistence** | `DatabaseManager.hpp`, `DatabaseManager.cpp` | [`backend/members/Member_07_File_Persistence_Database/`](./members/Member_07_File_Persistence_Database/) |
| **08** | *Member 8* | **Notification Service & Activity Queue** | `NotificationService.hpp`, `NotificationService.cpp` | [`backend/members/Member_08_Notifications_Analytics/`](./members/Member_08_Notifications_Analytics/) |
| **09** | *Member 9* | **System Utilities & JSON Parser** | `Utils.hpp`, `Utils.cpp`, `JsonHelper.hpp` | [`backend/members/Member_09_System_Utilities_Json/`](./members/Member_09_System_Utilities_Json/) |
| **10** | *Member 10* | **Data Seeder, CLI Terminal & Bootstrap**| `DataSeeder.hpp`, `DataSeeder.cpp`, `CLI.hpp`, `CLI.cpp`, `main.cpp` | [`backend/members/Member_10_Data_Seeder_CLI/`](./members/Member_10_Data_Seeder_CLI/) |

---

## 🛠️ How to Compile & Run the C++ Engine

### Quick Compile:
In the project root directory, simply run:
```bash
make
```
This builds the native binary `pixora` using `clang++ -std=c++17` with **zero external dependencies**!

### Execution Modes:

#### 1. Web Server Mode (Default)
```bash
./pixora --server 8080
# Or: make run
```
Starts the native C++ HTTP socket server on `http://localhost:8080`.  
It serves both the **HTML/CSS frontend** and the **C++ REST API endpoints** (`/api/pins`, `/api/profile`, etc.).

#### 2. Interactive Terminal CLI Mode (Great for College Viva!)
```bash
./pixora --cli
# Or: make cli
```
Launches an interactive menu-driven console program in your terminal. You can view feed items, search pins, create new pins, test like/save mechanics, inspect profiles, and save state to disk directly from the command line!

#### 3. Dual Mode (Web Server + Terminal Menu)
```bash
./pixora --both
# Or: make both
```
Launches the C++ Web Server in a background worker thread while keeping the terminal CLI interactive in your current terminal session.

---

## 🎓 C++ Viva / Oral Examination Cheatsheet

### 🔹 Member 01: Socket Programming & Multithreading
- **Q: How does the C++ HTTP server work?**  
  *Answer:* It uses POSIX stream sockets (`socket()`, `bind()`, `listen()`, `accept()`). For every incoming HTTP connection, it spawns a detached `std::thread` to read the request, resolve the path, and write the response headers and payload back to the socket.

### 🔹 Member 02: Pin Model & Vector Storage
- **Q: What OOP concepts does your Pin class implement?**  
  *Answer:* Encapsulation (private members accessed via getters/setters), Object Composition (composed of `Author` and `Comment` structs), and dynamic memory management using STL `std::vector<std::string>` for tags and `std::vector<Comment>` for discussions.

### 🔹 Member 03: Set Data Structures & Atomic State
- **Q: Why did you use `std::set` for following handles?**  
  *Answer:* `std::set` enforces uniqueness and provides $O(\log N)$ logarithmic time complexity for lookups, insertions, and deletions via an underlying balanced binary search tree (Red-Black Tree).

### 🔹 Member 04: Factory Pattern & Input Validation
- **Q: How is the Factory Pattern used in Pin creation?**  
  *Answer:* `PinCreator::createPin()` acts as a factory method. It validates input lengths, normalizes tag strings, binds author metadata, generates a unique ID, and returns an initialized `Pin` object.

### 🔹 Member 05: Class Invariants & Encapsulation
- **Q: Why are `pinCount` modifiers restricted to methods like `incrementPinCount()`?**  
  *Answer:* To protect the class invariant that a board's pin count cannot be negative. If `pinCount` were a raw public variable, external code could assign invalid values like `-5`.

### 🔹 Member 06: Algorithms & Lambda Comparators
- **Q: How does the search relevance ranking work?**  
  *Answer:* It computes a weighted score for each pin (Title = 10, Tags = 6, Board = 5, Category = 4, Author = 3, Description = 2), and uses `std::sort` with an inline C++ lambda expression to sort pins by score in descending order.

### 🔹 Member 07: File Streams & RAII
- **Q: How does C++ handle file persistence without memory leaks?**  
  *Answer:* Using the RAII (Resource Acquisition Is Initialization) pattern. `std::ofstream` opens the file upon construction and its destructor automatically closes the file descriptor when leaving scope, ensuring file handles are never leaked.

### 🔹 Member 08: Queue Buffers & Bound Limits
- **Q: How does the notification service prevent unbounded memory growth?**  
  *Answer:* It uses a fixed-capacity buffer. Whenever a new notification is prepended, if `notifications.size() > 50`, it calls `notifications.pop_back()` to discard the oldest item, keeping memory usage constant.

### 🔹 Member 09: String Manipulation & Custom JSON Parsing
- **Q: How do `Utils::trim()` and `JsonHelper` operate without third-party libraries?**  
  *Answer:* `Utils::trim()` uses `std::string::find_first_not_of` and `find_last_not_of`. `JsonHelper` scans JSON strings character by character, tracking quotes and escape sequences (`\"`) to extract string and integer values in $O(N)$ linear time.

### 🔹 Member 10: System Orchestration & Multithreaded Bootstrap
- **Q: How does `main.cpp` wire the entire C++ architecture together?**  
  *Answer:* It implements the Dependency Injection and Mediator patterns. `main.cpp` initializes the database, loads the pins into `FeedManager`, injects them into `InteractionManager`, `PinCreator`, and `NotificationService`, and passes these dependencies into `HttpServer` and `CLI`.
