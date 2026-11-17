/**
 * PIXORA - Responsive Engine, Theme Controller & Micro-Animations
 * Contributed by: Member 09 (Micro-Interactions, Animation & Responsive Mechanics)
 * 
 * Handles dark/light theme switching, button ripple effects, smooth card entrance
 * transitions, image blur-up loading, and mobile touch enhancements.
 */

class AnimationController {
    static init() {
        this.setupThemeToggle();
        this.setupImageBlurUp();
        this.setupIntersectionObserver();
        this.setupButtonRipples();
    }

    /**
     * Dark/Light Mode Theme Toggle
     */
    static setupThemeToggle() {
        const themeToggleBtn = document.getElementById('theme-toggle-btn');
        const savedTheme = localStorage.getItem('pixora_theme') || 'light';

        if (savedTheme === 'dark') {
            document.body.classList.add('dark-theme');
            this.updateThemeIcon(true);
        }

        if (themeToggleBtn) {
            themeToggleBtn.addEventListener('click', () => {
                const isDark = document.body.classList.toggle('dark-theme');
                localStorage.setItem('pixora_theme', isDark ? 'dark' : 'light');
                this.updateThemeIcon(isDark);
                ToastService.info(isDark ? 'Switched to Dark Mode 🌙' : 'Switched to Light Mode ☀️');
            });
        }
    }

    static updateThemeIcon(isDark) {
        const iconSpan = document.getElementById('theme-toggle-icon');
        if (!iconSpan) return;
        iconSpan.innerHTML = isDark 
            ? `<svg viewBox="0 0 24 24" width="18" height="18" fill="none" stroke="currentColor" stroke-width="2"><circle cx="12" cy="12" r="5"/><line x1="12" y1="1" x2="12" y2="3"/><line x1="12" y1="21" x2="12" y2="23"/><line x1="4.22" y1="4.22" x2="5.64" y2="5.64"/><line x1="18.36" y1="18.36" x2="19.78" y2="19.78"/><line x1="1" y1="12" x2="3" y2="12"/><line x1="21" y1="12" x2="23" y2="12"/><line x1="4.22" y1="19.78" x2="5.64" y2="18.36"/><line x1="18.36" y1="5.64" x2="19.78" y2="4.22"/></svg>`
            : `<svg viewBox="0 0 24 24" width="18" height="18" fill="none" stroke="currentColor" stroke-width="2"><path d="M21 12.79A9 9 0 1 1 11.21 3 7 7 0 0 0 21 12.79z"/></svg>`;
    }

    /**
     * Blur-up image transition
     */
    static setupImageBlurUp() {
        document.addEventListener('load', (e) => {
            if (e.target.tagName === 'IMG' && e.target.classList.contains('pin-image')) {
                e.target.classList.add('is-loaded');
            }
        }, true);
    }

    /**
     * Staggered card entrance on scroll
     */
    static setupIntersectionObserver() {
        if (!('IntersectionObserver' in window)) return;

        const observer = new IntersectionObserver((entries) => {
            entries.forEach(entry => {
                if (entry.isIntersecting) {
                    entry.target.classList.add('in-viewport');
                    observer.unobserve(entry.target);
                }
            });
        }, {
            threshold: 0.1,
            rootMargin: '50px'
        });

        const cards = document.querySelectorAll('.pin-card:not(.in-viewport)');
        cards.forEach(c => observer.observe(c));
    }

    /**
     * Subtle button ripple effect
     */
    static setupButtonRipples() {
        document.addEventListener('click', (e) => {
            const btn = e.target.closest('.pixora-btn-primary, .pin-action-btn');
            if (!btn) return;

            const rect = btn.getBoundingClientRect();
            const ripple = document.createElement('span');
            ripple.className = 'btn-ripple';
            const size = Math.max(rect.width, rect.height);
            ripple.style.width = ripple.style.height = `${size}px`;
            ripple.style.left = `${e.clientX - rect.left - size / 2}px`;
            ripple.style.top = `${e.clientY - rect.top - size / 2}px`;

            btn.appendChild(ripple);
            setTimeout(() => {
                ripple.remove();
            }, 600);
        });
    }
}
