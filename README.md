# Member 09: Micro-Animations, Theme Engine & Responsive Mechanics

## 👤 Member Information
- **Name / Assignee:** Member 09
- **Module Name:** Micro-Animations, Theming & Responsive Engine
- **Primary Source Files:** `frontend/js/animations.js`, `frontend/members/Member_09_Responsive_And_Animations/animations.css`

---

## 🎯 Contribution Overview
Member 09 elevated **PIXORA** from a static mockup into a modern, tactile, and highly responsive interactive product:
1. **Dark & Light Mode Theming**:
   - Complete design token palette for both Light and Dark themes.
   - Smooth theme transition button in the sidebar with sun/moon SVG icons.
   - User theme preference is saved to `localStorage` (`pixora_theme`) so the application remembers dark mode on subsequent visits.
2. **IntersectionObserver Card Transitions**:
   - Implements native browser `IntersectionObserver` to trigger smooth staggered entrance effects (`in-viewport`) as pins scroll into view.
3. **Progressive Image Blur-Up**:
   - Images render with a subtle soft blur and transition cleanly to full sharpness once loaded (`is-loaded` class).
4. **Button Click Ripples**:
   - Material-style radial ripple feedback on primary buttons and save toggles.
5. **Mobile Viewport Mechanics**:
   - Responsive breakpoints ensuring flawless UI across ultra-wide monitors (1920px), laptops (1440px), tablets (768px), and mobile devices (375px).

---

## 💻 Key Methods & Implementation Details
- `AnimationController.init()`: Boots the theme listener, image observer, and ripple handlers.
- `AnimationController.setupThemeToggle()`: Toggles the `dark-theme` class on `document.body` and stores preference.
- `AnimationController.setupIntersectionObserver()`: Registers card elements to watch when they scroll into the viewport.
- `AnimationController.setupButtonRipples()`: Calculates cursor click offsets (`clientX`, `clientY`) to render a smooth expanding ripple element.

---

## 🧪 How to Test This Module
1. Click the **Moon / Sun icon** at the bottom of the sidebar: verify the platform instantly switches to high-contrast Dark Mode with dark surface cards and glowing accents.
2. Refresh the browser: verify that Dark Mode remains active. Click again to return to Light Mode.
3. Scroll rapidly down the Home Feed: notice cards gently slide up and fade in as they enter your screen viewport.
4. Click on any primary red button (e.g. "Create a Pin"): notice the tactile ripple effect originating from where your cursor clicked.
5. In your browser DevTools, switch to Device Mode (iPhone / Pixel): observe how the sidebar transforms into the sleek bottom navigation bar.

---

## 🎓 Viva / Presentation Q&A Preparation
- **Q1: How does your Dark Mode implementation work under the hood?**  
  *Answer:* Through CSS Custom Properties (CSS variables). In `main.css`, default variables are defined under `:root`. When the user toggles dark mode, the `dark-theme` class is added to `document.body`, which overrides the background, surface, and text color variables across the entire application instantly.
- **Q2: Why use `IntersectionObserver` instead of listening to window `scroll` events?**  
  *Answer:* Window scroll events fire continuously and can cause severe frame drops (jank). `IntersectionObserver` is handled natively off the main thread by the browser engine, only executing our callback when an element actually crosses the viewport threshold.
- **Q3: How is the ripple effect calculated?**  
  *Answer:* We read `getBoundingClientRect()` of the clicked button, calculate the click coordinate relative to the button's origin (`e.clientX - rect.left`), and generate a dynamically sized expanding circle that removes itself after 600ms.
