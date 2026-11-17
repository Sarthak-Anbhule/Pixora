# Member 07: File Persistence & Database Layer

## 👤 Member Information
- **Name / Assignee:** Member 07
- **Role:** File Streams, Persistence & Database Management
- **Files Owned:** `DatabaseManager.hpp`, `DatabaseManager.cpp`
- **Core Technology:** C++17, File Streams (`std::ifstream`, `std::ofstream`), POSIX File System

---

## 🎯 Contribution Overview
Member 07 engineered the disk persistence layer that preserves application state:
1. **File Stream Persistence (`<fstream>`)**:
   - Manages reading and writing data to:
     - `backend/data/pins.json`
     - `backend/data/boards.json`
     - `backend/data/profile.json`
2. **Directory Management**:
   - Uses POSIX `stat()` and `mkdir()` to automatically verify and create the target data directory if it does not exist.
3. **Robust Array Parsing**:
   - Implements a brace-matching parser that reads multi-object JSON files safely, handling quotes and escaping without external dependencies.
4. **Failure Recovery**:
   - Checks `is_open()` and `good()` flags on file streams to ensure data integrity during disk writes.

---

## 💻 Key Methods
- `DatabaseManager::savePins(pins)`: Writes formatted JSON array to `pins.json`.
- `DatabaseManager::loadPins(outPins)`: Reads disk file and deserializes pin records into `std::vector<Pin>`.
- `DatabaseManager::saveBoards(boards)` / `loadBoards(outBoards)`
- `DatabaseManager::saveProfile(profile)` / `loadProfile(outProfile)`

---

## 🎓 C++ Viva / Oral Exam Questions & Answers
- **Q1: What stream classes in C++ did you use for file operations?**  
  *Answer:* We used `std::ofstream` (output file stream) for writing data to disk, `std::ifstream` (input file stream) for reading, and `std::stringstream` for buffering file contents into memory.
- **Q2: How do you verify if a file exists and was opened successfully in C++?**  
  *Answer:* By testing `file.is_open()` after construction and `file.good()` to verify the stream state flags (failbit, badbit, eofbit) are clear.
- **Q3: What is the RAII principle in C++ file streams?**  
  *Answer:* Resource Acquisition Is Initialization (RAII) means the file handle is acquired when the `std::ifstream`/`std::ofstream` object is constructed, and automatically closed when the stream object goes out of scope, preventing resource leaks.
