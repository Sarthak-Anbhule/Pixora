# Member 07: Storage & State Persistence Architecture

## 👤 Member Information
- **Name / Assignee:** Member 07
- **Module Name:** LocalStorage State Manager & Data Persistence Service
- **Primary Source Files:** `frontend/js/storage.js`

---

## 🎯 Contribution Overview
Member 07 engineered the central data backbone of **PIXORA**:
1. **Persistent State Engine**:
   - Manages all platform mutations (Pins, Boards, Likes, Saves, Following, Comments, User Profile) using the browser's `localStorage` API.
   - Built with automated schema seeding on first launch: populates the browser with 18+ rich pins, 5 boards, and full user profile data so the app looks completely alive out of the box.
2. **State Resilience & Fault Tolerance**:
   - Uses `try...catch` blocks and memory fallbacks to prevent crashes in private/incognito browsing modes or environments where storage is restricted.
3. **Reactive Query Methods**:
   - `getPins()` dynamically combines pin documents with current `isSaved` and `isLiked` sets.
   - `toggleSavePin(pinId, boardName)` atomically updates saved status, adjusts pin save counter, associates with target board, and updates profile counts.
   - `toggleLikePin(pinId)` handles optimistic liking and count increments.
   - `addComment(pinId, text)` records comments with timestamp and user avatar.
   - `createPin(pinData)` prepends new pins to the global feed, registers them under the author's created list, and updates board metrics.
4. **Clean Reset Mechanism**:
   - `resetToDefaults()` clears all cached keys and re-seeds clean demo data without requiring a browser cache wipe.

---

## 💻 Key Methods & Implementation Details
- `StorageManager.init()`: Checks storage keys and seeds default mock data if not found.
- `StorageManager.getPins()`: Returns all pins with fresh `isSaved` and `isLiked` boolean flags.
- `StorageManager.toggleSavePin(pinId, board)`: Adds or removes pin ID from saved set and writes to disk.
- `StorageManager.toggleLikePin(pinId)`: Toggles like state and increments/decrements like counter.
- `StorageManager.createPin(pinData)`: Generates a unique timestamped ID (`pin-17...`), assigns author metadata, and prepends to the pins collection.
- `StorageManager.updateProfile(updatedData)`: Persists profile edits.

---

## 🧪 How to Test This Module
1. Open the browser Developer Tools -> Application / Storage tab -> **Local Storage**.
2. Notice the keys: `pixora_pins_v1`, `pixora_saved_pin_ids_v1`, `pixora_liked_pin_ids_v1`, `pixora_boards_v1`, `pixora_user_profile_v1`.
3. Save or like a pin in the UI: observe the corresponding JSON values updating in Local Storage in real time.
4. Refresh the webpage completely (`F5` or `Cmd+R`): observe that your saved pins, likes, and comments persist seamlessly across page reloads!
5. Open the Settings modal and click **Reset Demo Data**: verify that storage is re-seeded cleanly.

---

## 🎓 Viva / Presentation Q&A Preparation
- **Q1: Why did you choose localStorage for persistence in this architecture?**  
  *Answer:* `localStorage` provides persistent key-value storage directly inside the client's browser (up to ~5MB), allowing the full frontend to function like a complete application with zero server setup required.
- **Q2: How do you handle serialization and deserialization?**  
  *Answer:* Complex objects and arrays are serialized into JSON strings with `JSON.stringify()` before writing to `localStorage`, and deserialized with `JSON.parse()` when reading back into memory.
- **Q3: How do you prevent errors if localStorage is disabled or corrupted?**  
  *Answer:* Through our `getRaw()` and `setRaw()` helper methods, all storage calls are wrapped in `try...catch` blocks that safely catch exceptions and fall back to memory defaults.
