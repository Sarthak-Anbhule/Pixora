/**
 * PIXORA - Toast Notification & Feedback System
 * Contributed by: Member 08 (Notifications & Micro-Interactions)
 * 
 * Provides animated, glassmorphic toast notifications with icons, action buttons,
 * and stacked auto-dismissing feedback messages.
 */

class ToastService {
    static container = null;

    static init() {
        if (!document.getElementById('pixora-toast-container')) {
            this.container = document.createElement('div');
            this.container.id = 'pixora-toast-container';
            this.container.className = 'pixora-toast-container';
            document.body.appendChild(this.container);
        } else {
            this.container = document.getElementById('pixora-toast-container');
        }
    }

    /**
     * Show a toast
     * @param {string} message 
     * @param {string} type 'success' | 'error' | 'info' | 'save'
     * @param {object} action optional { label: string, onClick: function }
     * @param {number} duration ms
     */
    static show(message, type = 'info', action = null, duration = 3400) {
        if (!this.container) this.init();

        const toast = document.createElement('div');
        toast.className = `pixora-toast toast-${type} animate-slide-up`;

        let iconSvg = '';
        switch (type) {
            case 'success':
            case 'save':
                iconSvg = `<svg viewBox="0 0 24 24" class="toast-icon" width="20" height="20" fill="none" stroke="currentColor" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round"><path d="M20 6L9 17l-5-5"/></svg>`;
                break;
            case 'error':
                iconSvg = `<svg viewBox="0 0 24 24" class="toast-icon" width="20" height="20" fill="none" stroke="currentColor" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round"><circle cx="12" cy="12" r="10"/><line x1="15" y1="9" x2="9" y2="15"/><line x1="9" y1="9" x2="15" y2="15"/></svg>`;
                break;
            case 'heart':
                iconSvg = `<svg viewBox="0 0 24 24" class="toast-icon text-red" width="20" height="20" fill="#E60023" stroke="#E60023" stroke-width="2"><path d="M19 14c1.49-1.46 3-3.21 3-5.5A5.5 5.5 0 0 0 16.5 3c-1.76 0-3 .5-4.5 2-1.5-1.5-2.74-2-4.5-2A5.5 5.5 0 0 0 2 8.5c0 2.3 1.5 4.05 3 5.5l7 7Z"/></svg>`;
                break;
            default:
                iconSvg = `<svg viewBox="0 0 24 24" class="toast-icon" width="20" height="20" fill="none" stroke="currentColor" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round"><circle cx="12" cy="12" r="10"/><line x1="12" y1="16" x2="12" y2="12"/><line x1="12" y1="8" x2="12.01" y2="8"/></svg>`;
        }

        let actionHtml = '';
        if (action && action.label) {
            actionHtml = `<button class="toast-action-btn">${action.label}</button>`;
        }

        toast.innerHTML = `
            <div class="toast-content">
                <span class="toast-icon-wrapper">${iconSvg}</span>
                <span class="toast-msg">${message}</span>
            </div>
            ${actionHtml}
            <button class="toast-close-btn" aria-label="Close notification">&times;</button>
        `;

        if (action && action.onClick) {
            const btn = toast.querySelector('.toast-action-btn');
            btn.addEventListener('click', (e) => {
                e.stopPropagation();
                action.onClick();
                this.dismiss(toast);
            });
        }

        const closeBtn = toast.querySelector('.toast-close-btn');
        closeBtn.addEventListener('click', () => this.dismiss(toast));

        this.container.appendChild(toast);

        // Auto dismiss timer
        const timer = setTimeout(() => {
            this.dismiss(toast);
        }, duration);

        toast._timer = timer;
    }

    static dismiss(toast) {
        if (!toast || toast._isDismissing) return;
        toast._isDismissing = true;
        clearTimeout(toast._timer);
        toast.classList.remove('animate-slide-up');
        toast.classList.add('animate-slide-down');
        setTimeout(() => {
            if (toast.parentNode) toast.parentNode.removeChild(toast);
        }, 300);
    }

    static success(msg, action) { this.show(msg, 'success', action); }
    static error(msg) { this.show(msg, 'error'); }
    static info(msg, action) { this.show(msg, 'info', action); }
    static save(msg, action) { this.show(msg, 'save', action); }
    static heart(msg) { this.show(msg, 'heart'); }
}
