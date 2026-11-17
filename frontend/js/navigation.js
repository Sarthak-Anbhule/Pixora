/**
 * PIXORA - Navigation, App Routing & Layout Controller
 * Contributed by: Member 01 (Navigation Shell & Application State Routing)
 * 
 * Controls view switching between Home, Explore, Create, Saved, and Profile views,
 * updates URL hash history, synchronizes sidebar, bottom navigation, and top bar states.
 */

class NavigationController {
    static views = ['home', 'explore', 'create', 'saved', 'profile'];
    static currentView = 'home';

    static init() {
        this.setupNavLinks();
        this.setupHeaderActions();
        this.setupSettingsModal();
        this.handleInitialRoute();
    }

    /**
     * Setup sidebar & bottom navigation clicks
     */
    static setupNavLinks() {
        // Desktop sidebar links
        const navButtons = document.querySelectorAll('[data-nav-target]');
        navButtons.forEach(btn => {
            btn.addEventListener('click', (e) => {
                e.preventDefault();
                const targetView = btn.getAttribute('data-nav-target');
                PixoraApp.navigateTo(targetView);
            });
        });

        // Brand logo click
        const logoBtn = document.getElementById('pixora-brand-logo');
        if (logoBtn) {
            logoBtn.addEventListener('click', () => {
                PixoraApp.navigateTo('home');
            });
        }

        // Header user avatar click
        const headerAvatar = document.getElementById('header-user-avatar-btn');
        if (headerAvatar) {
            headerAvatar.addEventListener('click', () => {
                PixoraApp.navigateTo('profile');
            });
        }
    }

    /**
     * Header notifications, messages, settings
     */
    static setupHeaderActions() {
        const notifBtn = document.getElementById('header-notif-btn');
        const notifDropdown = document.getElementById('header-notif-dropdown');
        if (notifBtn && notifDropdown) {
            notifBtn.addEventListener('click', (e) => {
                e.stopPropagation();
                notifDropdown.classList.toggle('is-active');
            });

            document.addEventListener('click', (e) => {
                if (!notifDropdown.contains(e.target) && e.target !== notifBtn) {
                    notifDropdown.classList.remove('is-active');
                }
            });
        }
    }

    /**
     * Setup settings / reset modal
     */
    static setupSettingsModal() {
        const settingsBtn = document.getElementById('sidebar-settings-btn');
        const settingsModal = document.getElementById('settings-modal');
        const closeBtn = document.getElementById('close-settings-modal');
        const resetDataBtn = document.getElementById('reset-demo-data-btn');

        if (settingsBtn && settingsModal) {
            settingsBtn.addEventListener('click', () => {
                settingsModal.classList.add('is-active');
            });
        }

        if (closeBtn && settingsModal) {
            closeBtn.addEventListener('click', () => {
                settingsModal.classList.remove('is-active');
            });
            settingsModal.addEventListener('click', (e) => {
                if (e.target === settingsModal) settingsModal.classList.remove('is-active');
            });
        }

        if (resetDataBtn) {
            resetDataBtn.addEventListener('click', () => {
                if (confirm('Reset all pins, boards, and saved items to initial demo state?')) {
                    StorageManager.resetToDefaults();
                    ToastService.success('Reset demo data successfully!');
                    if (settingsModal) settingsModal.classList.remove('is-active');
                    setTimeout(() => {
                        window.location.reload();
                    }, 500);
                }
            });
        }
    }

    /**
     * Check URL hash on load
     */
    static handleInitialRoute() {
        const hash = window.location.hash.replace(/^#/, '');
        if (hash.startsWith('pin=')) {
            const pinId = hash.replace('pin=', '');
            PixoraApp.navigateTo('home');
            setTimeout(() => {
                PinModal.open(pinId);
            }, 300);
        } else if (this.views.includes(hash)) {
            PixoraApp.navigateTo(hash);
        } else {
            PixoraApp.navigateTo('home');
        }

        window.addEventListener('popstate', () => {
            const curHash = window.location.hash.replace(/^#/, '');
            if (this.views.includes(curHash) && curHash !== PixoraApp.currentView) {
                PixoraApp.navigateTo(curHash, false);
            }
        });
    }

    /**
     * Switch view visibility and active nav indicator
     */
    static switchView(viewName, updateHash = true) {
        if (!this.views.includes(viewName)) viewName = 'home';
        this.currentView = viewName;

        if (updateHash) {
            window.location.hash = viewName;
        }

        // Hide all view panels
        this.views.forEach(v => {
            const el = document.getElementById(`view-${v}`);
            if (el) {
                if (v === viewName) {
                    el.classList.remove('hidden-view');
                    el.classList.add('active-view');
                } else {
                    el.classList.add('hidden-view');
                    el.classList.remove('active-view');
                }
            }
        });

        // Update nav buttons active classes
        const navButtons = document.querySelectorAll('[data-nav-target]');
        navButtons.forEach(btn => {
            if (btn.getAttribute('data-nav-target') === viewName) {
                btn.classList.add('is-active');
            } else {
                btn.classList.remove('is-active');
            }
        });

        // Scroll to top
        window.scrollTo({ top: 0, behavior: 'smooth' });
    }
}
