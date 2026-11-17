/**
 * PIXORA - Initial Mock Data & Asset Registry
 * Contributed by: Member 10 (Data Architecture & Asset Curation)
 * 
 * Provides diverse, high-resolution initial datasets for pins, boards,
 * categories, creators, and default profile settings.
 */

const INITIAL_CATEGORIES = [
    { id: 'all', name: 'All Inspiration', icon: 'sparkles' },
    { id: 'architecture', name: 'Architecture', icon: 'building' },
    { id: 'art-design', name: 'Art & Design', icon: 'palette' },
    { id: 'nature', name: 'Nature & Escapes', icon: 'mountain' },
    { id: 'photography', name: 'Photography', icon: 'camera' },
    { id: 'fashion', name: 'Fashion & Style', icon: 'shirt' },
    { id: 'tech', name: 'Tech & Workspaces', icon: 'laptop' },
    { id: 'interiors', name: 'Interior Decor', icon: 'armchair' },
    { id: 'food', name: 'Culinary Art', icon: 'utensils' },
    { id: 'travel', name: 'Travel Guides', icon: 'compass' },
    { id: 'minimalism', name: 'Minimalism', icon: 'feather' }
];

const INITIAL_BOARDS = [
    {
        id: 'board-1',
        title: 'Dream Architecture',
        description: 'Brutalist, organic, and ultra-modern spaces from around the world.',
        coverImage: 'https://images.unsplash.com/photo-1600585154340-be6161a56a0c?auto=format&fit=crop&w=800&q=80',
        pinCount: 6,
        isPrivate: false,
        createdAt: '2026-01-15'
    },
    {
        id: 'board-2',
        title: 'Minimalist Workspaces',
        description: 'Clean setups, mechanical keyboards, natural walnut desks and ambient lights.',
        coverImage: 'https://images.unsplash.com/photo-1518455027359-f3f8164ba6bd?auto=format&fit=crop&w=800&q=80',
        pinCount: 5,
        isPrivate: false,
        createdAt: '2026-02-01'
    },
    {
        id: 'board-3',
        title: 'Nordic & Earthy Tones',
        description: 'Ceramics, warm textiles, linen couches and soft afternoon sunlight.',
        coverImage: 'https://images.unsplash.com/photo-1586023492125-27b2c045efd7?auto=format&fit=crop&w=800&q=80',
        pinCount: 4,
        isPrivate: true,
        createdAt: '2026-02-12'
    },
    {
        id: 'board-4',
        title: 'Editorial & Street Style',
        description: 'High fashion silhouettes, monochrome looks, vintage leather jackets.',
        coverImage: 'https://images.unsplash.com/photo-1515886657613-9f3515b0c78f?auto=format&fit=crop&w=800&q=80',
        pinCount: 5,
        isPrivate: false,
        createdAt: '2026-02-20'
    },
    {
        id: 'board-5',
        title: 'Alpine Wanderlust',
        description: 'Misty pine valleys, glacial blue lakes, and cabin retreats.',
        coverImage: 'https://images.unsplash.com/photo-1506744038136-46273834b3fb?auto=format&fit=crop&w=800&q=80',
        pinCount: 4,
        isPrivate: false,
        createdAt: '2026-03-01'
    }
];

const INITIAL_PROFILE = {
    name: 'Elena Vance',
    handle: 'elenavance',
    title: 'Architectural Designer & Visual Curator',
    bio: 'Collecting light, brutalist shadows, timeless furniture, and serene travel moments. Based in Copenhagen 🇩🇰',
    avatar: 'https://images.unsplash.com/photo-1534528741775-53994a69daeb?auto=format&fit=crop&w=400&q=80',
    coverImage: 'https://images.unsplash.com/photo-1513694203232-719a280e022f?auto=format&fit=crop&w=1600&q=80',
    website: 'https://elenavance.design',
    location: 'Copenhagen, Denmark',
    followersCount: 1840,
    followingCount: 392,
    savesCount: 148,
    isCurrentUser: true
};

const INITIAL_PINS = [
    {
        id: 'pin-1',
        title: 'The Concrete Monolith Residence',
        description: 'Cantilevered architectural residence nestled into limestone cliffs overlooking the Mediterranean sea.',
        imageUrl: 'https://images.unsplash.com/photo-1600585154340-be6161a56a0c?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'tall',
        height: 520,
        category: 'architecture',
        board: 'Dream Architecture',
        tags: ['minimalism', 'concrete', 'brutalism', 'villa'],
        sourceUrl: 'https://archdaily.com/concrete-monolith',
        likes: 342,
        saves: 189,
        isLiked: false,
        isSaved: true,
        author: {
            name: 'Kasper Lindqvist',
            handle: 'kasperlind',
            avatar: 'https://images.unsplash.com/photo-1507003211169-0a1dd7228f2d?auto=format&fit=crop&w=200&q=80',
            verified: true,
            followers: 12500
        },
        comments: [
            { id: 'c-1', user: { name: 'Sophia Chen', avatar: 'https://images.unsplash.com/photo-1517841905240-472988babdf9?auto=format&fit=crop&w=200&q=80' }, text: 'The cantilever structural engineering here is pure genius.', timestamp: '2 hours ago' },
            { id: 'c-2', user: { name: 'Elena Vance', avatar: 'https://images.unsplash.com/photo-1534528741775-53994a69daeb?auto=format&fit=crop&w=200&q=80' }, text: 'That rough concrete texture against the smooth glass facade is breathtaking!', timestamp: '1 day ago' }
        ],
        createdAt: '2026-02-10'
    },
    {
        id: 'pin-2',
        title: 'Minimalist Oak & Matte Studio Setup',
        description: 'An ergonomic creative workspace featuring a solid white oak desk, wireless peripherals, and diffused warm bias lighting.',
        imageUrl: 'https://images.unsplash.com/photo-1518455027359-f3f8164ba6bd?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'medium',
        height: 420,
        category: 'tech',
        board: 'Minimalist Workspaces',
        tags: ['workspace', 'desksetup', 'minimalist', 'tech'],
        sourceUrl: 'https://minimaldesks.io/oak-studio',
        likes: 512,
        saves: 290,
        isLiked: true,
        isSaved: true,
        author: {
            name: 'Marcus Brody',
            handle: 'brodystudio',
            avatar: 'https://images.unsplash.com/photo-1500648767791-00dcc994a43e?auto=format&fit=crop&w=200&q=80',
            verified: false,
            followers: 6300
        },
        comments: [
            { id: 'c-3', user: { name: 'Alex Rivera', avatar: 'https://images.unsplash.com/photo-1492562080023-ab3db95bfbce?auto=format&fit=crop&w=200&q=80' }, text: 'Where did you get that monitor riser?', timestamp: '3 hours ago' }
        ],
        createdAt: '2026-02-12'
    },
    {
        id: 'pin-3',
        title: 'Nordic Ceramic vessels & Wabi-Sabi Styling',
        description: 'Handcrafted stoneware ceramics styled with dried pampas grass and gentle morning shadows.',
        imageUrl: 'https://images.unsplash.com/photo-1578749556568-bc2c40e68b61?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'tall',
        height: 560,
        category: 'interiors',
        board: 'Nordic & Earthy Tones',
        tags: ['ceramics', 'wabisabi', 'interior', 'handmade'],
        sourceUrl: 'https://ceramicjournal.org/wabi-sabi',
        likes: 215,
        saves: 130,
        isLiked: false,
        isSaved: false,
        author: {
            name: 'Astrid Møller',
            handle: 'astridmoller',
            avatar: 'https://images.unsplash.com/photo-1544005313-94ddf0286df2?auto=format&fit=crop&w=200&q=80',
            verified: true,
            followers: 9800
        },
        comments: [],
        createdAt: '2026-02-14'
    },
    {
        id: 'pin-4',
        title: 'Emerald Lake & Misty Pine Peaks',
        description: 'Reflective alpine waters deep within the Canadian Rockies at sunrise before the hikers arrive.',
        imageUrl: 'https://images.unsplash.com/photo-1506744038136-46273834b3fb?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'medium',
        height: 440,
        category: 'nature',
        board: 'Alpine Wanderlust',
        tags: ['mountains', 'lake', 'canada', 'nature', 'landscape'],
        sourceUrl: 'https://nationalgeographic.com/rockies',
        likes: 890,
        saves: 610,
        isLiked: true,
        isSaved: false,
        author: {
            name: 'Oliver Thorne',
            handle: 'oliverwild',
            avatar: 'https://images.unsplash.com/photo-1522075469751-3a6694fb2f61?auto=format&fit=crop&w=200&q=80',
            verified: true,
            followers: 34100
        },
        comments: [
            { id: 'c-4', user: { name: 'Elena Vance', avatar: 'https://images.unsplash.com/photo-1534528741775-53994a69daeb?auto=format&fit=crop&w=200&q=80' }, text: 'The water clarity is unreal! Putting this on my bucket list.', timestamp: '5 hours ago' }
        ],
        createdAt: '2026-02-15'
    },
    {
        id: 'pin-5',
        title: 'Oversized Tailored Trench & French Chignon',
        description: 'Autumn capsule wardrobe inspiration with camel wool trench coat, leather loafers, and minimal golden hoop earrings.',
        imageUrl: 'https://images.unsplash.com/photo-1515886657613-9f3515b0c78f?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'ultra-tall',
        height: 610,
        category: 'fashion',
        board: 'Editorial & Street Style',
        tags: ['fashion', 'streetstyle', 'autumn', 'minimalist'],
        sourceUrl: 'https://vogue.com/capsule-style',
        likes: 470,
        saves: 340,
        isLiked: false,
        isSaved: true,
        author: {
            name: 'Camille Laurent',
            handle: 'camilleinparis',
            avatar: 'https://images.unsplash.com/photo-1494790108377-be9c29b29330?auto=format&fit=crop&w=200&q=80',
            verified: true,
            followers: 41200
        },
        comments: [],
        createdAt: '2026-02-18'
    },
    {
        id: 'pin-6',
        title: 'Sun-Drenched Brutalist Spiral Staircase',
        description: 'Geometric shadows dancing across sweeping cast-in-place concrete curves in Valencia.',
        imageUrl: 'https://images.unsplash.com/photo-1513694203232-719a280e022f?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'medium',
        height: 450,
        category: 'architecture',
        board: 'Dream Architecture',
        tags: ['geometry', 'shadows', 'stairs', 'concrete'],
        sourceUrl: 'https://architecturaldigest.com/valencia',
        likes: 620,
        saves: 415,
        isLiked: true,
        isSaved: false,
        author: {
            name: 'Kasper Lindqvist',
            handle: 'kasperlind',
            avatar: 'https://images.unsplash.com/photo-1507003211169-0a1dd7228f2d?auto=format&fit=crop&w=200&q=80',
            verified: true,
            followers: 12500
        },
        comments: [],
        createdAt: '2026-02-20'
    },
    {
        id: 'pin-7',
        title: 'Artisan Matcha Latte & Ceramic Bowl',
        description: 'Single-origin ceremonial Uji matcha whisked to velvet foam with bamboo chasen.',
        imageUrl: 'https://images.unsplash.com/photo-1536256263959-770b48d82b0a?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'tall',
        height: 500,
        category: 'food',
        board: 'Nordic & Earthy Tones',
        tags: ['matcha', 'tea', 'japan', 'wellness', 'aesthetic'],
        sourceUrl: 'https://kinfolk.com/matcha-ceremony',
        likes: 310,
        saves: 180,
        isLiked: false,
        isSaved: false,
        author: {
            name: 'Hana Takahashi',
            handle: 'hanacraft',
            avatar: 'https://images.unsplash.com/photo-1534528741775-53994a69daeb?auto=format&fit=crop&w=200&q=80',
            verified: false,
            followers: 4700
        },
        comments: [],
        createdAt: '2026-02-21'
    },
    {
        id: 'pin-8',
        title: 'Tokyo Nocturne & Rainy Neon Alley',
        description: 'CineStill 800T 35mm film photograph capturing neon sign reflections on wet Shinjuku pavement.',
        imageUrl: 'https://images.unsplash.com/photo-1503899036084-c55cdd92da26?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'tall',
        height: 540,
        category: 'photography',
        board: 'Creative Inspiration',
        tags: ['tokyo', 'filmphotography', 'neon', 'nightlife', 'cinematic'],
        sourceUrl: 'https://filmmag.io/tokyo-35mm',
        likes: 994,
        saves: 720,
        isLiked: true,
        isSaved: true,
        author: {
            name: 'Kenji Sato',
            handle: 'kenjifilm',
            avatar: 'https://images.unsplash.com/photo-1500648767791-00dcc994a43e?auto=format&fit=crop&w=200&q=80',
            verified: true,
            followers: 28900
        },
        comments: [
            { id: 'c-5', user: { name: 'Oliver Thorne', avatar: 'https://images.unsplash.com/photo-1522075469751-3a6694fb2f61?auto=format&fit=crop&w=200&q=80' }, text: 'That halation on the red lantern glow is unmistakable CineStill.', timestamp: '1 day ago' }
        ],
        createdAt: '2026-02-23'
    },
    {
        id: 'pin-9',
        title: 'Mid-Century Modern Lounge & Linen Drapery',
        description: 'Eames lounge chair alongside fluted travertine coffee table in a serene loft bathed in soft afternoon glow.',
        imageUrl: 'https://images.unsplash.com/photo-1586023492125-27b2c045efd7?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'medium',
        height: 430,
        category: 'interiors',
        board: 'Nordic & Earthy Tones',
        tags: ['midcentury', 'interior', 'eames', 'livingroom', 'decor'],
        sourceUrl: 'https://dwell.com/serene-living',
        likes: 670,
        saves: 450,
        isLiked: false,
        isSaved: true,
        author: {
            name: 'Astrid Møller',
            handle: 'astridmoller',
            avatar: 'https://images.unsplash.com/photo-1544005313-94ddf0286df2?auto=format&fit=crop&w=200&q=80',
            verified: true,
            followers: 9800
        },
        comments: [],
        createdAt: '2026-02-25'
    },
    {
        id: 'pin-10',
        title: 'Cyberpunk Interface & Spatial Design Concept',
        description: 'Figma glassmorphism UI elements, dark mode neon accents, and three-dimensional holographic widgets.',
        imageUrl: 'https://images.unsplash.com/photo-1618005182384-a83a8bd57fbe?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'ultra-tall',
        height: 590,
        category: 'art-design',
        board: 'Creative Inspiration',
        tags: ['ui', 'ux', 'futuristic', 'glassmorphism', 'design'],
        sourceUrl: 'https://behance.net/spatial-interface',
        likes: 820,
        saves: 530,
        isLiked: true,
        isSaved: false,
        author: {
            name: 'Liam Croft',
            handle: 'liamcroft_ui',
            avatar: 'https://images.unsplash.com/photo-1535713875002-d1d0cf377fde?auto=format&fit=crop&w=200&q=80',
            verified: false,
            followers: 7400
        },
        comments: [],
        createdAt: '2026-02-28'
    },
    {
        id: 'pin-11',
        title: 'Dolomites Sharp Peaks & Jagged Ridge',
        description: 'The golden hour striking Seceda mountain ridge in Northern Italy with drifting clouds below.',
        imageUrl: 'https://images.unsplash.com/photo-1464822759023-fed622ff2c3b?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'tall',
        height: 510,
        category: 'travel',
        board: 'Alpine Wanderlust',
        tags: ['dolomites', 'italy', 'alps', 'hiking', 'wanderlust'],
        sourceUrl: 'https://lonelyplanet.com/dolomites-trek',
        likes: 1240,
        saves: 880,
        isLiked: true,
        isSaved: true,
        author: {
            name: 'Oliver Thorne',
            handle: 'oliverwild',
            avatar: 'https://images.unsplash.com/photo-1522075469751-3a6694fb2f61?auto=format&fit=crop&w=200&q=80',
            verified: true,
            followers: 34100
        },
        comments: [],
        createdAt: '2026-03-01'
    },
    {
        id: 'pin-12',
        title: 'Minimalist Typography: Form Follows Silence',
        description: 'Swiss style typographic grid poster exploration using Neue Haas Grotesk and dynamic white space.',
        imageUrl: 'https://images.unsplash.com/photo-1579783900882-c0d3dad7b119?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'medium',
        height: 460,
        category: 'art-design',
        board: 'Creative Inspiration',
        tags: ['poster', 'typography', 'swiss', 'graphicdesign'],
        sourceUrl: 'https://printmag.com/swiss-poster',
        likes: 410,
        saves: 260,
        isLiked: false,
        isSaved: false,
        author: {
            name: 'Elena Vance',
            handle: 'elenavance',
            avatar: 'https://images.unsplash.com/photo-1534528741775-53994a69daeb?auto=format&fit=crop&w=200&q=80',
            verified: true,
            followers: 1840
        },
        comments: [],
        createdAt: '2026-03-02'
    },
    {
        id: 'pin-13',
        title: 'Artisan Sourdough & Fresh Rosemary Focaccia',
        description: 'Slow-fermented wild yeast open crumb focaccia adorned with heirloom cherry tomatoes and Maldon sea salt.',
        imageUrl: 'https://images.unsplash.com/photo-1509440159596-0249088772ff?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'tall',
        height: 490,
        category: 'food',
        board: 'Nordic & Earthy Tones',
        tags: ['baking', 'sourdough', 'focaccia', 'culinary', 'homemade'],
        sourceUrl: 'https://bonappetit.com/wild-sourdough',
        likes: 580,
        saves: 370,
        isLiked: false,
        isSaved: false,
        author: {
            name: 'Chloe Durand',
            handle: 'chloebakes',
            avatar: 'https://images.unsplash.com/photo-1517841905240-472988babdf9?auto=format&fit=crop&w=200&q=80',
            verified: false,
            followers: 8200
        },
        comments: [],
        createdAt: '2026-03-03'
    },
    {
        id: 'pin-14',
        title: 'Sculptural Marble Coffee Table & Modernist Rug',
        description: 'Honest Nero Marquina marble curves paired with hand-tufted geometric wool rug.',
        imageUrl: 'https://images.unsplash.com/photo-1618221195710-dd6b41faaea6?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'medium',
        height: 440,
        category: 'interiors',
        board: 'Dream Architecture',
        tags: ['interior', 'marble', 'livingroom', 'sculpture'],
        sourceUrl: 'https://architecturaldigest.com/sculptural-spaces',
        likes: 390,
        saves: 210,
        isLiked: false,
        isSaved: true,
        author: {
            name: 'Kasper Lindqvist',
            handle: 'kasperlind',
            avatar: 'https://images.unsplash.com/photo-1507003211169-0a1dd7228f2d?auto=format&fit=crop&w=200&q=80',
            verified: true,
            followers: 12500
        },
        comments: [],
        createdAt: '2026-03-04'
    },
    {
        id: 'pin-15',
        title: 'Nordic Black Cabin in Snowy Pine Woods',
        description: 'Off-grid A-frame retreat featuring floor-to-ceiling glass in the deep winter landscape of Norway.',
        imageUrl: 'https://images.unsplash.com/photo-1510798831971-661eb04b3739?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'ultra-tall',
        height: 600,
        category: 'architecture',
        board: 'Dream Architecture',
        tags: ['cabin', 'norway', 'snow', 'winter', 'architecture'],
        sourceUrl: 'https://cabinporn.net/norwegian-black-cabin',
        likes: 1530,
        saves: 1120,
        isLiked: true,
        isSaved: true,
        author: {
            name: 'Kasper Lindqvist',
            handle: 'kasperlind',
            avatar: 'https://images.unsplash.com/photo-1507003211169-0a1dd7228f2d?auto=format&fit=crop&w=200&q=80',
            verified: true,
            followers: 12500
        },
        comments: [],
        createdAt: '2026-03-05'
    },
    {
        id: 'pin-16',
        title: 'Minimalist Mechanical Keyboard & Keycaps',
        description: 'Custom gasket mounted 65% CNC anodized aluminium keyboard with botanical PBT keycaps.',
        imageUrl: 'https://images.unsplash.com/photo-1587829741301-dc798b83add3?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'medium',
        height: 420,
        category: 'tech',
        board: 'Minimalist Workspaces',
        tags: ['keyboard', 'customkeeb', 'desksetup', 'aesthetic'],
        sourceUrl: 'https://reddit.com/r/MechanicalKeyboards',
        likes: 720,
        saves: 480,
        isLiked: false,
        isSaved: false,
        author: {
            name: 'Marcus Brody',
            handle: 'brodystudio',
            avatar: 'https://images.unsplash.com/photo-1500648767791-00dcc994a43e?auto=format&fit=crop&w=200&q=80',
            verified: false,
            followers: 6300
        },
        comments: [],
        createdAt: '2026-03-06'
    },
    {
        id: 'pin-17',
        title: 'Vintage Leica M6 & Black & White Portra',
        description: 'Rangefinder street photography gear on weathered Italian leather pouch.',
        imageUrl: 'https://images.unsplash.com/photo-1516035069371-29a1b244cc32?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'tall',
        height: 510,
        category: 'photography',
        board: 'Creative Inspiration',
        tags: ['leica', 'film', 'vintage', 'camera', 'gear'],
        sourceUrl: 'https://leica-camera.com',
        likes: 640,
        saves: 410,
        isLiked: false,
        isSaved: false,
        author: {
            name: 'Kenji Sato',
            handle: 'kenjifilm',
            avatar: 'https://images.unsplash.com/photo-1500648767791-00dcc994a43e?auto=format&fit=crop&w=200&q=80',
            verified: true,
            followers: 28900
        },
        comments: [],
        createdAt: '2026-03-07'
    },
    {
        id: 'pin-18',
        title: 'Botanical Illustration & Wildflowers Risograph',
        description: 'Two-color Risograph print depicting meadow wildflowers on speckled heavy cotton paper.',
        imageUrl: 'https://images.unsplash.com/photo-1579783902614-a3fb3927b675?auto=format&fit=crop&w=800&q=80',
        aspectRatio: 'tall',
        height: 530,
        category: 'art-design',
        board: 'Creative Inspiration',
        tags: ['risograph', 'illustration', 'botanical', 'print'],
        sourceUrl: 'https://itsnicethat.com/risograph-wild',
        likes: 490,
        saves: 330,
        isLiked: true,
        isSaved: false,
        author: {
            name: 'Sophia Chen',
            handle: 'sophiachen_art',
            avatar: 'https://images.unsplash.com/photo-1517841905240-472988babdf9?auto=format&fit=crop&w=200&q=80',
            verified: false,
            followers: 5100
        },
        comments: [],
        createdAt: '2026-03-08'
    }
];
