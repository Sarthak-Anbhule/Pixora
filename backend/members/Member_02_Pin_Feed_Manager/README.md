# Member 02: Pin Model & Feed Management Architecture

## 👤 Member Information
- **Name / Assignee:** Member 02
- **Role:** Pin Data Model & Feed In-Memory Management
- **Files Owned:** `Pin.hpp`, `Pin.cpp`, `FeedManager.hpp`, `FeedManager.cpp`
- **Core Technology:** C++17, OOP, STL Containers (`std::vector`, `std::string`)

---

## 🎯 Contribution Overview
Member 02 designed the foundational **Pin Data Model** and the **In-Memory Feed Controller**:
1. **Object-Oriented Data Encapsulation**:
   - `Author` struct: models creators with name, handle, avatar URL, verification status, and follower count.
   - `Comment` struct: models discussions with unique IDs, user identity, text, and relative timestamps.
   - `Pin` class: encapsulates title, description, image URL, aspect ratio, board, tags (`std::vector<std::string>`), likes, saves, and timestamps with private member variables and public accessor/mutator methods.
2. **State Mutator Logic**:
   - `toggleLike()`: increments or decrements like counter based on state.
   - `toggleSave(targetBoard)`: tracks bookmarks and updates collection association.
3. **Feed Collection Management (`FeedManager`)**:
   - Manages the primary `std::vector<Pin>` list.
   - Provides methods for prepending/appending pins, ID lookup, removal via `std::remove_if`, and board-specific queries (`getPinsByBoard`).
4. **Serialization**:
   - Serializes Pin objects and lists into standard JSON strings using `std::ostringstream`.

---

## 💻 Key Methods
- `Pin::toJson()`: Serializes Pin properties, nested Author, tags array, and comments into JSON format.
- `Pin::fromJson(json)`: Deserializes JSON string into a structured `Pin` instance.
- `FeedManager::addPin(pin, prepend)`: Inserts new pin at front (`pins.insert(pins.begin(), pin)`) or back.
- `FeedManager::findPinById(id)`: Performs linear search across pins vector.

---

## 🎓 C++ Viva / Oral Exam Questions & Answers
- **Q1: What OOP principles are demonstrated in your Pin class?**  
  *Answer:* **Encapsulation** (private member variables protected behind getters/setters), **Data Abstraction** (hiding internal state changes like `toggleLike()` from callers), and **Composition** (the `Pin` class is composed of `Author` and `Comment` objects).
- **Q2: Why did you use `std::vector` for storing pins instead of a raw array?**  
  *Answer:* `std::vector` is a dynamic array that manages its own memory on the heap, automatically resizes when new pins are added, and provides bounds safety and standard STL iterator support.
- **Q3: How does `FeedManager::removePin` work?**  
  *Answer:* It uses the standard erase-remove idiom with `std::remove_if` and a lambda predicate: `pins.erase(std::remove_if(...), pins.end())`.
