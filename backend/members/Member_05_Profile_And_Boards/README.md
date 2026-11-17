# Member 05: User Profile & Board Collections

## 👤 Member Information
- **Name / Assignee:** Member 05
- **Role:** Profile Architecture & Board Collections
- **Files Owned:** `Profile.hpp`, `Profile.cpp`, `Board.hpp`, `Board.cpp`
- **Core Technology:** C++17, OOP Encapsulation, JSON Serialization

---

## 🎯 Contribution Overview
Member 05 authored the **User Profile and Board Data Models**:
1. **User Profile Modeling (`Profile`)**:
   - Encapsulates display name, handle (`@elenavance`), title, biography, avatar URL, cover image URL, location, and website link.
   - Manages statistics counters: `followersCount`, `followingCount`, and `savesCount`.
2. **Board Collections (`Board`)**:
   - Encapsulates collection title, description, cover image URL, pin count, creation timestamp, and secret/private board status (`isPrivate`).
3. **Serialization & Deserialization**:
   - Provides clean `toJson()` methods using `std::ostringstream` and `fromJson()` deserialization parsers for disk storage and HTTP API responses.

---

## 💻 Key Methods
- `Profile::toJson()` / `Profile::fromJson()`
- `Board::toJson()` / `Board::fromJson()`
- `Board::incrementPinCount()` / `Board::decrementPinCount()`

---

## 🎓 C++ Viva / Oral Exam Questions & Answers
- **Q1: Why are getters and setters preferred over public member variables in C++?**  
  *Answer:* Getters and setters enforce **encapsulation**. They protect class invariants (for example, ensuring `pinCount` cannot become negative with `decrementPinCount()`), allow validation when variables are updated, and decouple class internals from external callers.
- **Q2: What is the purpose of the default constructor in `Board` and `Profile`?**  
  *Answer:* Default constructors initialize member variables to safe default values (e.g. `pinCount = 0`, `isPrivate = false`) and set timestamps via `Utils::getCurrentDate()`, preventing undefined behavior from uninitialized variables.
- **Q3: How do you format numbers and boolean types in C++ JSON serialization?**  
  *Answer:* In `toJson()`, numbers are appended directly to `std::ostringstream` without quotes (`<< pinCount`), while booleans are output as `(isPrivate ? "true" : "false")`.
