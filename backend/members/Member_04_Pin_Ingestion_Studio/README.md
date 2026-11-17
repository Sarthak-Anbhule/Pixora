# Member 04: Pin Ingestion Studio & Media Validator

## 👤 Member Information
- **Name / Assignee:** Sarthak Anbhule (Member 04)
- **Role:** Pin Ingestion, Validation & Tag Parsing
- **Files Owned:** `PinCreator.hpp`, `PinCreator.cpp`
- **Core Technology:** C++17, String Parsing, Validation Pipelines

---

## 🎯 Contribution Overview
Member 04 implemented the **Pin Creation & Validation Engine**:
1. **Input Sanitization & Validation**:
   - Trims whitespace from titles, descriptions, image URLs, and tags.
   - Rejects empty titles or missing images with descriptive error messages.
2. **Tag Parsing & Normalization**:
   - Parses comma-separated tag lists (`"minimalism, #modern, design"`), strips leading `#` characters, and populates the pin's `std::vector<std::string>` tags list.
3. **JSON Deserialization Pipeline**:
   - `createPinFromJson(json, outPin, outError)`: Extracts payload attributes from incoming HTTP POST requests or file imports and passes them through the validation pipeline.
4. **Feed Insertion**:
   - Automatically attaches author identity from the active user Profile, flags the new pin as saved, and prepends it to the front of `FeedManager`.

---

## 💻 Key Methods
- `PinCreator::createPin(...)`: Core factory method validating inputs and instantiating a new `Pin`.
- `PinCreator::createPinFromJson(...)`: Parses HTTP request body JSON and invokes `createPin()`.

---

## 🎓 C++ Viva / Oral Exam Questions & Answers
- **Q1: How do you handle string validation in C++?**  
  *Answer:* We use helper functions like `Utils::trim()` to remove leading and trailing whitespace, then check `str.empty()`. If validation fails, we set an error string and return `false`.
- **Q2: What is the Factory Pattern and how is it used here?**  
  *Answer:* `PinCreator::createPin` acts as a factory method. Instead of callers manually creating and configuring a `Pin` instance, `PinCreator` encapsulates ID generation, author metadata association, timestamp setting, and validation before returning the instantiated object.
- **Q3: How are tags tokenized in C++?**  
  *Answer:* We use `std::istringstream` and `std::getline(stream, token, ',')` to split the comma-delimited string, followed by trimming and stripping leading `#` characters.
