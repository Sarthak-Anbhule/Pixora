/**
 * PIXORA - Member 10 Contribution Module
 * Subsystem: Data Architecture, Asset Curation & App Integration
 * 
 * Responsibilities:
 * - High-resolution initial dataset curation (18+ rich pins across 10 diverse categories).
 * - Variable aspect ratio definitions to showcase the authentic Pinterest masonry effect.
 * - Initial board definitions, creator profiles, and realistic discussion threads.
 * - Master integration and bootstrap orchestration (`PixoraApp`).
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
