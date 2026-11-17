# 🎨 PIXORA — Member 04 Contribution Branch
### 👤 Author: Sarthak Anbhule (Member 04)
### 📌 Subsystem: Pin Creation Studio & Media Ingestion (Frontend + C++ Backend)

---

## 🌟 Executive Summary
This branch contains all engineering contributions for **Member 04 (Sarthak Anbhule)** on project **PIXORA**:
- **Frontend Architecture:** Interactive **Pin Creator Studio** using HTML5 Drag-and-Drop, `FileReader` API for Base64 image ingestion, inline board creator, and real-time form validation.
- **Backend Architecture:** Modern C++17 **Pin Ingestion & Media Processing Service** (`PinCreator.hpp`, `PinCreator.cpp`) implementing input sanitization, tag tokenization, author metadata binding, and REST endpoint integration (`POST /api/pins`).

---

## 📁 Member 04 Files Inventory

```
PIXORA/ (Sarthak Branch)
├── README.md                                           # Member 04 Master Documentation & Viva Guide
├── frontend/
│   ├── members/
│   │   └── Member_04_Pin_Creator_Studio/
│   │       ├── pin_creator.js                          # Member 04 Standalone Frontend Controller
│   │       └── README.md                               # Member 04 Frontend Technical Report
│   ├── js/
│   │   └── create.js                                   # Core Pin Creator Studio Logic
│   └── css/
│       └── create.css                                  # Studio UI Styling, Dropzone & Form Controls
└── backend/
    ├── members/
    │   └── Member_04_Pin_Ingestion_Studio/
    │       ├── PinCreator.hpp                          # Member 04 C++ Class Declaration
    │       ├── PinCreator.cpp                          # Member 04 C++ Class Implementation
    │       └── README.md                               # Member 04 C++ Technical Report
    ├── include/
    │   └── PinCreator.hpp                              # C++ Header File
    └── src/
        └── PinCreator.cpp                              # C++ Implementation File
```

---

## 🎯 Features Implemented by Sarthak Anbhule

### 1. HTML5 Drag-and-Drop File Ingestion
- Configured drag event listeners (`dragenter`, `dragover`, `dragleave`, `drop`) on `#create-dropzone` with visual highlight states (`.drag-active`).
- Captures dropped files directly from the user's operating system with `e.dataTransfer.files`.

### 2. Zero-Server Base64 Image Processing
- Integrated the browser's native `FileReader` API (`reader.readAsDataURL(file)`).
- Converts local image files into base64 Data URLs so images can be stored and rendered immediately in the browser and passed to C++ without requiring external cloud storage (AWS S3).

### 3. Image URL Preloader & Validator
- Built an image URL loader with real-time validation using `new Image()`.
- Verifies that remote URLs load cleanly before updating the preview, triggering error toasts for broken links.

### 4. Inline Dynamic Board Creation
- Synchronizes with existing boards from storage.
- Features an inline `+ New Board` toggle that lets users create and select a new board collection right from the creation form without losing their draft.

### 5. C++ Backend Ingestion Pipeline (`PinCreator.cpp`)
- Implemented `PinCreator::createPin()` and `PinCreator::createPinFromJson()` in C++17.
- Enforces data integrity: trims strings, checks non-empty titles, validates image URLs, and generates unique IDs via `Utils::generateId("pin")`.
- Parses comma-delimited tags into an STL `std::vector<std::string>` and strips leading `#` characters.
- Automatically binds active creator identity from the user's `Profile` model and prepends the new pin to the top of `FeedManager`.

---

## 🎓 College Viva / Oral Exam Questions & Answers for Sarthak

### Q1: What specific part of PIXORA did you build?
> **Answer:**  
> *"I was Member 04, responsible for the **Pin Creation Studio & Media Ingestion** across both the frontend and C++ backend. On the frontend, I developed the drag-and-drop upload zone, Base64 image ingestion using JavaScript's `FileReader` API, and inline board creation. On the C++ backend, I authored the `PinCreator` class, which handles input validation, tag parsing, author metadata binding, and JSON payload handling for the `POST /api/pins` endpoint."*

### Q2: How did you implement local image uploads without a cloud storage service like AWS S3?
> **Answer:**  
> *"I used the HTML5 `FileReader` API. When a user drags an image or picks a file, `FileReader.readAsDataURL(file)` reads the raw binary file from the user's machine and encodes it into a standard Base64 Data URL string. This string can be stored directly in `localStorage` or transmitted via JSON to our C++ backend, allowing the image to render seamlessly in any browser without needing third-party cloud hosting."*

### Q3: How does your C++ `PinCreator` class validate and process incoming pin requests?
> **Answer:**  
> *"In `PinCreator::createPin()`, I first trim whitespace using `Utils::trim()`. I verify that the title and image URL are non-empty, returning descriptive error messages if validation fails. I then parse comma-separated tags by tokenizing the string with `std::istringstream`, strip leading `#` symbols, generate a collision-free ID with `Utils::generateId("pin")`, bind the current author profile, and insert the pin at the front of `FeedManager` using `pins.insert(pins.begin(), pin)`."*

### Q4: How does the Drag-and-Drop mechanism work in vanilla JavaScript?
> **Answer:**  
> *"We listen to standard HTML5 drag events on the dropzone: `dragover`, `dragleave`, and `drop`. In the `dragover` handler, calling `e.preventDefault()` is essential to stop the browser from opening the dropped image in a new tab. When the user drops the file, we access `e.dataTransfer.files[0]`, validate that its MIME type starts with `image/`, check that it is under our 4MB safety threshold, and pass it to our `FileReader` pipeline."*

### Q5: What design patterns did you use in your C++ code?
> **Answer:**  
> *"I used the **Factory Method Pattern** in `PinCreator`. Instead of client code or HTTP controllers manually assembling a `Pin` with all its dependencies, `PinCreator::createPin()` acts as a centralized factory that validates inputs, attaches default board and category settings, binds author metadata, initializes like/save counters, and returns a fully initialized `Pin` object."*

---

## 🛠️ How to Test Sarthak's Module

1. Open PIXORA in your browser (`http://localhost:8080`).
2. Click the **`+`** icon on the sidebar to open the **Create Pin Studio**.
3. Drag any image file from your computer onto the dropzone or click one of the quick sample pills (e.g. *"Skyscraper"*).
4. Enter a title and description, click **+ New Board** to create a custom board, and enter tags (e.g. `minimalism, modern, design`).
5. Click **Publish Pin**: notice the toast notification appears and the new pin appears at the top of the feed!
6. In the terminal CLI (`./pixora --cli`), select option `[3] Create a New Pin` to test Sarthak's C++ validation directly from the command line!
