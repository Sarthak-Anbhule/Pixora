#include "DataSeeder.hpp"

namespace Pixora {

Profile DataSeeder::getInitialProfile() {
    return Profile();
}

std::vector<Board> DataSeeder::getInitialBoards() {
    std::vector<Board> boards;
    boards.push_back(Board("board-1", "Dream Architecture", "Brutalist, organic, and ultra-modern spaces.", "https://images.unsplash.com/photo-1600585154340-be6161a56a0c?auto=format&fit=crop&w=800&q=80", 6, false));
    boards.push_back(Board("board-2", "Minimalist Workspaces", "Clean setups, mechanical keyboards, natural walnut desks.", "https://images.unsplash.com/photo-1518455027359-f3f8164ba6bd?auto=format&fit=crop&w=800&q=80", 5, false));
    boards.push_back(Board("board-3", "Nordic & Earthy Tones", "Ceramics, warm textiles, linen couches and soft light.", "https://images.unsplash.com/photo-1586023492125-27b2c045efd7?auto=format&fit=crop&w=800&q=80", 4, true));
    boards.push_back(Board("board-4", "Editorial & Street Style", "High fashion silhouettes, monochrome looks, vintage leather.", "https://images.unsplash.com/photo-1515886657613-9f3515b0c78f?auto=format&fit=crop&w=800&q=80", 5, false));
    boards.push_back(Board("board-5", "Alpine Wanderlust", "Misty pine valleys, glacial blue lakes, and cabin retreats.", "https://images.unsplash.com/photo-1506744038136-46273834b3fb?auto=format&fit=crop&w=800&q=80", 4, false));
    return boards;
}

std::vector<Pin> DataSeeder::getInitialPins() {
    std::vector<Pin> pins;

    // Pin 1
    Author a1{"Kasper Lindqvist", "kasperlind", "https://images.unsplash.com/photo-1507003211169-0a1dd7228f2d?auto=format&fit=crop&w=200&q=80", true, 12500};
    Pin p1("pin-1", "The Concrete Monolith Residence", "Cantilevered architectural residence nestled into limestone cliffs.", "https://images.unsplash.com/photo-1600585154340-be6161a56a0c?auto=format&fit=crop&w=800&q=80", "architecture", "Dream Architecture", a1);
    p1.setSourceUrl("https://archdaily.com/concrete-monolith");
    p1.setLikes(342);
    p1.setSaves(189);
    p1.setIsSaved(true);
    p1.setAspectRatio("tall");
    p1.setHeight(520);
    p1.addTag("minimalism"); p1.addTag("concrete"); p1.addTag("brutalism");
    p1.addComment({"c-1", "Sophia Chen", "https://images.unsplash.com/photo-1517841905240-472988babdf9?auto=format&fit=crop&w=200&q=80", "The cantilever structural engineering here is pure genius.", "2 hours ago"});
    pins.push_back(p1);

    // Pin 2
    Author a2{"Marcus Brody", "brodystudio", "https://images.unsplash.com/photo-1500648767791-00dcc994a43e?auto=format&fit=crop&w=200&q=80", false, 6300};
    Pin p2("pin-2", "Minimalist Oak & Matte Studio Setup", "An ergonomic workspace featuring solid white oak desk and warm lighting.", "https://images.unsplash.com/photo-1518455027359-f3f8164ba6bd?auto=format&fit=crop&w=800&q=80", "tech", "Minimalist Workspaces", a2);
    p2.setSourceUrl("https://minimaldesks.io");
    p2.setLikes(512);
    p2.setSaves(290);
    p2.setIsLiked(true);
    p2.setIsSaved(true);
    p2.setAspectRatio("medium");
    p2.setHeight(420);
    p2.addTag("workspace"); p2.addTag("desksetup"); p2.addTag("minimalist");
    pins.push_back(p2);

    // Pin 3
    Author a3{"Astrid Møller", "astridmoller", "https://images.unsplash.com/photo-1544005313-94ddf0286df2?auto=format&fit=crop&w=200&q=80", true, 9800};
    Pin p3("pin-3", "Nordic Ceramic vessels & Wabi-Sabi Styling", "Handcrafted stoneware ceramics styled with dried pampas grass.", "https://images.unsplash.com/photo-1578749556568-bc2c40e68b61?auto=format&fit=crop&w=800&q=80", "interiors", "Nordic & Earthy Tones", a3);
    p3.setLikes(215);
    p3.setSaves(130);
    p3.setAspectRatio("tall");
    p3.setHeight(560);
    p3.addTag("ceramics"); p3.addTag("wabisabi"); p3.addTag("interior");
    pins.push_back(p3);

    // Pin 4
    Author a4{"Oliver Thorne", "oliverwild", "https://images.unsplash.com/photo-1522075469751-3a6694fb2f61?auto=format&fit=crop&w=200&q=80", true, 34100};
    Pin p4("pin-4", "Emerald Lake & Misty Pine Peaks", "Reflective alpine waters deep within the Canadian Rockies at sunrise.", "https://images.unsplash.com/photo-1506744038136-46273834b3fb?auto=format&fit=crop&w=800&q=80", "nature", "Alpine Wanderlust", a4);
    p4.setLikes(890);
    p4.setSaves(610);
    p4.setIsLiked(true);
    p4.setAspectRatio("medium");
    p4.setHeight(440);
    p4.addTag("mountains"); p4.addTag("canada"); p4.addTag("nature");
    pins.push_back(p4);

    // Pin 5
    Author a5{"Camille Laurent", "camilleinparis", "https://images.unsplash.com/photo-1494790108377-be9c29b29330?auto=format&fit=crop&w=200&q=80", true, 41200};
    Pin p5("pin-5", "Oversized Tailored Trench & French Chignon", "Autumn capsule wardrobe inspiration with camel wool trench coat.", "https://images.unsplash.com/photo-1515886657613-9f3515b0c78f?auto=format&fit=crop&w=800&q=80", "fashion", "Editorial & Street Style", a5);
    p5.setLikes(470);
    p5.setSaves(340);
    p5.setIsSaved(true);
    p5.setAspectRatio("ultra-tall");
    p5.setHeight(610);
    p5.addTag("fashion"); p5.addTag("streetstyle"); p5.addTag("autumn");
    pins.push_back(p5);

    // Pin 6
    Pin p6("pin-6", "Sun-Drenched Brutalist Spiral Staircase", "Geometric shadows dancing across sweeping cast concrete curves.", "https://images.unsplash.com/photo-1513694203232-719a280e022f?auto=format&fit=crop&w=800&q=80", "architecture", "Dream Architecture", a1);
    p6.setLikes(620);
    p6.setSaves(415);
    p6.setAspectRatio("medium");
    p6.setHeight(450);
    p6.addTag("geometry"); p6.addTag("stairs"); p6.addTag("concrete");
    pins.push_back(p6);

    // Pin 7
    Author a6{"Kenji Sato", "kenjifilm", "https://images.unsplash.com/photo-1500648767791-00dcc994a43e?auto=format&fit=crop&w=200&q=80", true, 28900};
    Pin p7("pin-7", "Tokyo Nocturne & Rainy Neon Alley", "CineStill 800T 35mm photograph capturing neon sign reflections.", "https://images.unsplash.com/photo-1503899036084-c55cdd92da26?auto=format&fit=crop&w=800&q=80", "photography", "Creative Inspiration", a6);
    p7.setLikes(994);
    p7.setSaves(720);
    p7.setIsLiked(true);
    p7.setIsSaved(true);
    p7.setAspectRatio("tall");
    p7.setHeight(540);
    p7.addTag("tokyo"); p7.addTag("filmphotography"); p7.addTag("neon");
    pins.push_back(p7);

    // Pin 8
    Pin p8("pin-8", "Mid-Century Modern Lounge & Linen Drapery", "Eames lounge chair alongside fluted travertine coffee table.", "https://images.unsplash.com/photo-1586023492125-27b2c045efd7?auto=format&fit=crop&w=800&q=80", "interiors", "Nordic & Earthy Tones", a3);
    p8.setLikes(670);
    p8.setSaves(450);
    p8.setIsSaved(true);
    p8.setAspectRatio("medium");
    p8.setHeight(430);
    p8.addTag("midcentury"); p8.addTag("interior"); p8.addTag("eames");
    pins.push_back(p8);

    // Pin 9
    Pin p9("pin-9", "Nordic Black Cabin in Snowy Pine Woods", "Off-grid A-frame retreat featuring floor-to-ceiling glass in Norway.", "https://images.unsplash.com/photo-1510798831971-661eb04b3739?auto=format&fit=crop&w=800&q=80", "architecture", "Dream Architecture", a1);
    p9.setLikes(1530);
    p9.setSaves(1120);
    p9.setIsLiked(true);
    p9.setIsSaved(true);
    p9.setAspectRatio("ultra-tall");
    p9.setHeight(600);
    p9.addTag("cabin"); p9.addTag("norway"); p9.addTag("snow");
    pins.push_back(p9);

    // Pin 10
    Author a7{"Elena Vance", "elenavance", "https://images.unsplash.com/photo-1534528741775-53994a69daeb?auto=format&fit=crop&w=200&q=80", true, 1840};
    Pin p10("pin-10", "Minimalist Typography: Form Follows Silence", "Swiss style typographic grid poster exploration using Neue Haas Grotesk.", "https://images.unsplash.com/photo-1579783900882-c0d3dad7b119?auto=format&fit=crop&w=800&q=80", "art-design", "Creative Inspiration", a7);
    p10.setLikes(410);
    p10.setSaves(260);
    p10.setAspectRatio("medium");
    p10.setHeight(460);
    p10.addTag("poster"); p10.addTag("typography"); p10.addTag("swiss");
    pins.push_back(p10);

    return pins;
}

} // namespace Pixora
