# Member 08: Toast Notifications & User Feedback System

## 👤 Member Information
- **Name / Assignee:** Member 08
- **Module Name:** Real-time Toast Notifications & Interactive Feedback Service
- **Primary Source Files:** `frontend/js/notifications.js`, `frontend/members/Member_08_Notifications_And_Feedback/notifications.css`

---

## 🎯 Contribution Overview
Member 08 developed the UI micro-feedback and alerting infrastructure for **PIXORA**:
1. **Dynamic Toast Notification Engine**:
   - Injects a responsive fixed container in the bottom right on desktop and centered on mobile.
   - Supports stacked notifications that auto-dismiss smoothly after 3.4 seconds.
2. **Context-Aware Alert Types**:
   - `ToastService.success()`: Green checkmark icon for successful creations and edits.
   - `ToastService.save()`: Custom save feedback indicating the target board.
   - `ToastService.heart()`: Red heart reaction for like feedback.
   - `ToastService.error()`: Crimson warning icon for validation failures.
   - `ToastService.info()`: Informational updates (theme switch, link copied).
3. **Interactive Action Pills**:
   - Toasts can contain functional action buttons (e.g. `[View]` or `[Undo]`) that trigger callback functions when clicked.
4. **Fluid Motion Physics**:
   - Custom CSS keyframe transitions: `animate-slide-up` on arrival and `animate-slide-down` on dismissal.
   - Manual dismiss button (X) for immediate user control.

---

## 💻 Key Methods & Implementation Details
- `ToastService.init()`: Ensures the global toast container element exists in `document.body`.
- `ToastService.show(message, type, action, duration)`: Creates the toast DOM element, attaches SVG icons, configures action callbacks, and sets up the auto-dismiss timer.
- `ToastService.dismiss(toast)`: Clears timer, initiates slide-down animation, and safely unmounts the node from the DOM after 300ms.
- Semantic aliases: `ToastService.success()`, `ToastService.save()`, `ToastService.error()`, `ToastService.heart()`, `ToastService.info()`.

---

## 🧪 How to Test This Module
1. Click the red **Save** button on any pin: notice the toast in the bottom-right corner saying *"Saved to 'Dream Architecture' [View]"*.
2. Click the **[View]** action button inside that toast: notice it immediately navigates you to your Saved Pins collection!
3. Click the heart icon on a pin: verify the toast displays a red heart icon saying *"Liked pin"*.
4. Go to **Create Pin** and click **Publish Pin** without uploading an image: verify an error toast with warning icon appears saying *"Please provide an image for your pin."*
5. Click the **X** on any toast: verify it dismisses immediately without waiting for the timer.

---

## 🎓 Viva / Presentation Q&A Preparation
- **Q1: Why use a centralized Toast Service instead of standard browser `alert()`?**  
  *Answer:* Standard `alert()` blocks the JavaScript runtime thread, looks generic, and disrupts user flow. Our custom `ToastService` is asynchronous, non-blocking, beautifully animated, supports custom action buttons, and integrates with the app's visual theme.
- **Q2: How do you prevent memory leaks when toasts are removed?**  
  *Answer:* `clearTimeout(toast._timer)` is called to clear any pending timers, and the element is removed from the DOM with `toast.parentNode.removeChild(toast)`.
- **Q3: How do toasts adapt between desktop and mobile screens?**  
  *Answer:* On desktop, toasts anchor to `bottom: 24px; right: 24px`. On screens <= 768px, media queries adjust the container to sit above the mobile bottom navigation bar (`bottom: calc(var(--bottom-nav-height) + 16px)`) and expand across the mobile width.
