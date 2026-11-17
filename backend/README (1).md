# Member 08: Notification & Analytics Service

## 👤 Member Information
- **Name / Assignee:** Member 08
- **Role:** Notification Queue & Activity Analytics
- **Files Owned:** `NotificationService.hpp`, `NotificationService.cpp`
- **Core Technology:** C++17, Queue Management, Event Dispatching

---

## 🎯 Contribution Overview
Member 08 built the **Notification & Event Logging Service**:
1. **Activity Notification Modeling (`NotificationItem`)**:
   - Models activity entries with unique ID, message text, event category (`like`, `save`, `follow`, `comment`, `create`), author avatar, and relative timestamp.
2. **In-Memory Notification Buffer**:
   - Prepend-based queue where newest activities appear first (`notifications.insert(notifications.begin(), item)`).
   - Bounds buffer size to 50 items (`notifications.pop_back()`) to prevent unbounded memory growth.
3. **Seed Baseline Generator**:
   - Seeds realistic initial notifications on launch so the activity center displays active community engagement immediately.
4. **JSON Serialization**:
   - Formats the event queue into JSON array payloads for the `/api/notifications` HTTP endpoint.

---

## 💻 Key Methods
- `NotificationService::addNotification(message, type, avatar)`
- `NotificationService::getNotifications()`
- `NotificationService::toJson()`
- `NotificationService::seedInitialNotifications()`

---

## 🎓 C++ Viva / Oral Exam Questions & Answers
- **Q1: How do you prevent the notifications vector from consuming excessive memory?**  
  *Answer:* In `addNotification()`, after prepending the new item, we check `if (notifications.size() > 50) notifications.pop_back();`. This maintains a fixed-capacity ring-like buffer of the 50 most recent events.
- **Q2: What is the difference between `std::vector::push_back` and `std::vector::insert`?**  
  *Answer:* `push_back()` appends an element to the end of the vector in amortized $O(1)$ time, while `insert(begin(), ...)` places the element at the beginning, shifting existing elements by one position ($O(N)$ time).
- **Q3: How are notification event categories managed?**  
  *Answer:* Through string tokens (`"like"`, `"save"`, `"follow"`, `"comment"`), which the HTTP server and frontend use to render appropriate icons and visual highlights.
