/**
 * PIXORA - Member 04 Contribution Module
 * Subsystem: Pin Creation Studio & Media Ingestion
 * 
 * Responsibilities:
 * - Drag-and-drop file upload zone with visual drop indicators.
 * - FileReader API integration for local image processing (Data URL / base64).
 * - Direct image URL loading with validation.
 * - Inline dynamic board creation.
 * - Form validation and pin publishing to localStorage.
 */

class PinCreator {
    static form = null;
    static previewContainer = null;
    static currentImageData = null;

    static init() {
        this.form = document.getElementById('create-pin-form');
        this.previewContainer = document.getElementById('create-dropzone');
        if (!this.form) return;

        this.setupMediaInputs();
        this.setupBoardSelector();
        this.setupFormSubmission();
        this.setupSampleSuggestions();
    }

    static setupMediaInputs() {
        const dropZone = document.getElementById('create-dropzone');
        const fileInput = document.getElementById('create-file-input');
        const urlInput = document.getElementById('create-image-url');
        const loadUrlBtn = document.getElementById('load-url-btn');

        if (!dropZone) return;

        ['dragenter', 'dragover'].forEach(name => {
            dropZone.addEventListener(name, (e) => {
                e.preventDefault();
                e.stopPropagation();
                dropZone.classList.add('drag-active');
            });
        });

        ['dragleave', 'drop'].forEach(name => {
            dropZone.addEventListener(name, (e) => {
                e.preventDefault();
                e.stopPropagation();
                dropZone.classList.remove('drag-active');
            });
        });

        dropZone.addEventListener('drop', (e) => {
            const files = e.dataTransfer.files;
            if (files && files[0]) {
                this.handleLocalFile(files[0]);
            }
        });

        dropZone.addEventListener('click', (e) => {
            if (e.target.id === 'create-file-input' || e.target.closest('#create-image-url') || e.target.closest('#load-url-btn') || e.target.closest('.sample-pill')) return;
            if (fileInput) fileInput.click();
        });

        if (fileInput) {
            fileInput.addEventListener('change', (e) => {
                if (e.target.files && e.target.files[0]) {
                    this.handleLocalFile(e.target.files[0]);
                }
            });
        }

        if (loadUrlBtn && urlInput) {
            loadUrlBtn.addEventListener('click', (e) => {
                e.preventDefault();
                e.stopPropagation();
                this.handleImageUrl(urlInput.value);
            });

            urlInput.addEventListener('keydown', (e) => {
                if (e.key === 'Enter') {
                    e.preventDefault();
                    this.handleImageUrl(urlInput.value);
                }
            });
        }
    }

    static handleLocalFile(file) {
        if (!file.type.startsWith('image/')) {
            ToastService.error('Please upload an image file (PNG, JPG, WEBP).');
            return;
        }

        if (file.size > 4 * 1024 * 1024) {
            ToastService.error('Image size exceeds 4MB limit.');
            return;
        }

        const reader = new FileReader();
        reader.onload = (e) => {
            this.setPreview(e.target.result);
            ToastService.success('Image loaded from device!');
        };
        reader.onerror = () => {
            ToastService.error('Failed to read image file.');
        };
        reader.readAsDataURL(file);
    }

    static handleImageUrl(url) {
        if (!url || !url.trim()) {
            ToastService.error('Please enter a valid image URL');
            return;
        }

        const cleanUrl = url.trim();
        const testImg = new Image();
        testImg.onload = () => {
            this.setPreview(cleanUrl);
            ToastService.success('Image loaded from URL!');
        };
        testImg.onerror = () => {
            ToastService.error('Could not load image from this URL. Check the link.');
        };
        testImg.src = cleanUrl;
    }

    static setPreview(src) {
        this.currentImageData = src;
        const dropZone = document.getElementById('create-dropzone');
        if (!dropZone) return;

        dropZone.innerHTML = `
            <div class="active-preview-container">
                <img src="${src}" alt="Pin Preview" class="active-preview-img" />
                <button type="button" class="remove-preview-btn" id="remove-preview-btn" title="Remove image">
                    <svg viewBox="0 0 24 24" width="18" height="18" fill="none" stroke="currentColor" stroke-width="2.5"><line x1="18" y1="6" x2="6" y2="18"/><line x1="6" y1="6" x2="18" y2="18"/></svg>
                </button>
            </div>
        `;

        const removeBtn = document.getElementById('remove-preview-btn');
        if (removeBtn) {
            removeBtn.addEventListener('click', (e) => {
                e.stopPropagation();
                this.resetDropzone();
            });
        }
    }

    static resetDropzone() {
        this.currentImageData = null;
        const dropZone = document.getElementById('create-dropzone');
        if (!dropZone) return;

        dropZone.innerHTML = `
            <input type="file" id="create-file-input" accept="image/*" class="visually-hidden" />
            <div class="dropzone-empty-content">
                <div class="upload-icon-circle">
                    <svg viewBox="0 0 24 24" width="28" height="28" fill="none" stroke="currentColor" stroke-width="2"><path d="M21 15v4a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2v-4"/><polyline points="17 8 12 3 7 8"/><line x1="12" y1="3" x2="12" y2="15"/></svg>
                </div>
                <h4 class="upload-heading">Choose a file or drag and drop it here</h4>
                <p class="upload-sub">We recommend high-quality .jpg or .png files under 4MB</p>
                <div class="url-input-strip" onclick="event.stopPropagation()">
                    <input type="url" id="create-image-url" placeholder="Or paste an image URL..." class="url-input" />
                    <button type="button" id="load-url-btn" class="url-btn">Load</button>
                </div>
                <div class="sample-images-bar" onclick="event.stopPropagation()">
                    <span class="sample-label">Quick samples:</span>
                    <button type="button" class="sample-pill" data-sample="https://images.unsplash.com/photo-1541701494587-cb58502866ab?auto=format&fit=crop&w=800&q=80">Minimal Art</button>
                    <button type="button" class="sample-pill" data-sample="https://images.unsplash.com/photo-1486406146926-c627a92ad1ab?auto=format&fit=crop&w=800&q=80">Skyscraper</button>
                    <button type="button" class="sample-pill" data-sample="https://images.unsplash.com/photo-1507525428034-b723cf961d3e?auto=format&fit=crop&w=800&q=80">Tropical Beach</button>
                </div>
            </div>
        `;

        this.setupMediaInputs();
        this.setupSampleSuggestions();
    }

    static setupBoardSelector() {
        const boardSelect = document.getElementById('create-board-select');
        if (!boardSelect) return;

        const boards = StorageManager.getBoards();
        boardSelect.innerHTML = boards.map(b => `<option value="${b.title}">${b.title}</option>`).join('');

        const inlineNewBoardBtn = document.getElementById('inline-new-board-btn');
        const inlineBoardGroup = document.getElementById('inline-new-board-group');
        const inlineSaveBoardBtn = document.getElementById('inline-save-board-btn');
        const inlineBoardInput = document.getElementById('inline-new-board-input');

        if (inlineNewBoardBtn && inlineBoardGroup) {
            inlineNewBoardBtn.addEventListener('click', () => {
                inlineBoardGroup.classList.toggle('hidden');
                if (!inlineBoardGroup.classList.contains('hidden') && inlineBoardInput) {
                    inlineBoardInput.focus();
                }
            });
        }

        if (inlineSaveBoardBtn && inlineBoardInput) {
            inlineSaveBoardBtn.addEventListener('click', () => {
                const name = inlineBoardInput.value.trim();
                if (!name) {
                    ToastService.error('Please enter a board name');
                    return;
                }
                const newB = StorageManager.createBoard({ title: name });
                if (newB) {
                    this.setupBoardSelector();
                    boardSelect.value = newB.title;
                    inlineBoardInput.value = '';
                    inlineBoardGroup.classList.add('hidden');
                    ToastService.success(`Board "${newB.title}" created!`);
                }
            });
        }
    }

    static setupSampleSuggestions() {
        const pills = document.querySelectorAll('.sample-pill');
        pills.forEach(pill => {
            pill.addEventListener('click', (e) => {
                e.stopPropagation();
                const url = pill.getAttribute('data-sample');
                this.setPreview(url);
                ToastService.info('Sample image loaded!');
            });
        });
    }

    static setupFormSubmission() {
        if (!this.form) return;

        this.form.addEventListener('submit', (e) => {
            e.preventDefault();

            if (!this.currentImageData) {
                ToastService.error('Please provide an image for your pin.');
                return;
            }

            const titleInput = document.getElementById('create-pin-title');
            const descInput = document.getElementById('create-pin-desc');
            const linkInput = document.getElementById('create-pin-link');
            const boardSelect = document.getElementById('create-board-select');
            const categorySelect = document.getElementById('create-pin-category');
            const tagsInput = document.getElementById('create-pin-tags');

            const title = titleInput ? titleInput.value.trim() : '';
            if (!title) {
                ToastService.error('Please enter a title for your pin.');
                if (titleInput) titleInput.focus();
                return;
            }

            let tags = [];
            if (tagsInput && tagsInput.value) {
                tags = tagsInput.value.split(',').map(t => t.trim().replace(/^#/, '')).filter(Boolean);
            }

            const newPin = StorageManager.createPin({
                title: title,
                description: descInput ? descInput.value.trim() : '',
                imageUrl: this.currentImageData,
                sourceUrl: linkInput ? linkInput.value.trim() : '',
                board: boardSelect ? boardSelect.value : 'Creative Inspiration',
                category: categorySelect ? categorySelect.value : 'art-design',
                tags: tags
            });

            this.form.reset();
            this.resetDropzone();

            ToastService.success('Pin published to your board and feed!', {
                label: 'View Pin',
                onClick: () => PinModal.open(newPin.id)
            });

            PixoraApp.navigateTo('home');
        });
    }
}
