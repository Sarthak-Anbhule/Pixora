# Member 03: Social Interaction Engine

## 👤 Member Information
- **Name / Assignee:** Member 03
- **Role:** Social Feedback & Reaction Controller
- **Files Owned:** `InteractionManager.hpp`, `InteractionManager.cpp`
- **Core Technology:** C++17, STL Sets (`std::set`), Reference Semantics

---

## 🎯 Contribution Overview
Member 03 authored the **Social Interaction Engine** that coordinates likes, saves, comments, and author follow states:
1. **Atomic Interaction Toggles**:
   - `toggleLike(pinId, outLikes)`: Finds target pin and toggles its like state, updating likes counter.
   - `toggleSave(pinId, boardName, outSaves)`: Manages saved state, moves pin into target board collection, and synchronizes profile total saves count.
2. **Comment Submission Pipeline**:
   - `addComment(pinId, authorName, avatar, text, outComment)`: Validates text, auto-generates a timestamped comment ID, constructs a `Comment` struct, and attaches it to the pin.
3. **Follower Tracking System**:
   - Manages followed user handles using an STL `std::set<std::string>` to guarantee unique handle entries and $O(\log N)$ lookup efficiency.
   - Automatically synchronizes `Profile::followingCount`.

---

## 💻 Key Methods
- `InteractionManager::toggleLike(pinId, &outLikes)`
- `InteractionManager::toggleSave(pinId, boardName, &outSaves)`
- `InteractionManager::addComment(pinId, name, avatar, text, &outComment)`
- `InteractionManager::toggleFollow(handle)`
- `InteractionManager::isFollowing(handle)`

---

## 🎓 C++ Viva / Oral Exam Questions & Answers
- **Q1: Why did you use `std::set<std::string>` for storing followed authors?**  
  *Answer:* `std::set` is backed by a self-balancing binary search tree (Red-Black Tree). It guarantees that author handles are unique (no duplicate follows) and provides $O(\log N)$ logarithmic time complexity for insertions, deletions, and lookups.
- **Q2: Why does `InteractionManager` receive `FeedManager` and `Profile` by reference?**  
  *Answer:* Passing by reference (`FeedManager&`, `Profile&`) avoids expensive deep copying of all pins and profile data, and allows `InteractionManager` to directly mutate the shared application state.
- **Q3: How are output parameters used in `toggleLike` and `toggleSave`?**  
  *Answer:* We return a boolean indicating success or active state, and use non-const reference output parameters (`int& outLikes`) to return the updated numeric counter to the caller in a single function call.
