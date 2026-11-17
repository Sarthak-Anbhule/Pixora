# Member 09: System Utilities & JSON Parser Engine

## 👤 Member Information
- **Name / Assignee:** Member 09
- **Role:** String Utilities, JSON Extraction & System Helpers
- **Files Owned:** `Utils.hpp`, `Utils.cpp`, `JsonHelper.hpp`
- **Core Technology:** C++17, String Algorithms, Custom Lightweight JSON Parser

---

## 🎯 Contribution Overview
Member 09 built the foundational **Utilities & JSON Parsing Subsystem** used by all other 9 members:
1. **String Manipulation Algorithms (`Utils`)**:
   - `trim()`: Removes whitespace (`\t`, `\n`, `\r`, spaces) from both ends of a string.
   - `toLowerCase()`: Converts strings to lowercase using `std::transform` and `std::tolower`.
   - `split()`: Tokenizes delimited strings using `std::istringstream` and `std::getline`.
   - `urlDecode()`: Converts URL percent-encoding (e.g. `%20` to space) and `+` symbols.
   - `escapeJson()`: Escapes control characters, quotes (`\"`), and newlines for valid JSON payloads.
2. **Lightweight JSON Extractor (`JsonHelper`)**:
   - Zero-dependency string-scanning parser that extracts values from raw JSON strings without requiring external libraries:
     - `JsonHelper::getString(json, key)`
     - `JsonHelper::getInt(json, key)`
     - `JsonHelper::getBool(json, key)`
     - `JsonHelper::getArrayOfStrings(json, key)`
3. **ID & Timestamp Generation**:
   - `generateId(prefix)`: Generates collision-resistant IDs using millisecond epochs from `<chrono>` and pseudo-random numbers from `<random>`.
   - `getCurrentDate()`: Generates ISO date strings (`YYYY-MM-DD`).

---

## 💻 Key Methods
- `Utils::trim(str)`
- `Utils::toLowerCase(str)`
- `Utils::split(str, delimiter)`
- `Utils::escapeJson(str)`
- `Utils::urlDecode(str)`
- `JsonHelper::getString(json, key, fallback)`
- `JsonHelper::getInt(json, key, fallback)`

---

## 🎓 C++ Viva / Oral Exam Questions & Answers
- **Q1: Why did you write custom JSON and string utilities instead of installing third-party libraries?**  
  *Answer:* To ensure zero external dependencies. The entire PIXORA C++ project compiles directly on any computer with standard `clang++` or `g++` without needing package managers like vcpkg, conan, or Homebrew.
- **Q2: How does `Utils::trim` achieve $O(N)$ efficiency?**  
  *Answer:* Using `find_first_not_of` and `find_last_not_of` on `std::string`. It identifies the bounds in two quick scans and extracts the trimmed substring with a single `substr()` call.
- **Q3: How does `JsonHelper::getString` handle nested strings and escaping?**  
  *Answer:* It locates the `"<key>":` token, skips whitespace, identifies opening quotes `"`, and advances until an unescaped closing quote (`json[end] == '"' && json[end-1] != '\\'`) is found.
