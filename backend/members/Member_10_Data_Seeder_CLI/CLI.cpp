#include "CLI.hpp"
#include "SearchEngine.hpp"
#include "Utils.hpp"
#include <iostream>
#include <iomanip>

namespace Pixora {

CLI::CLI(FeedManager& feed, Profile& prof, std::vector<Board>& b,
         InteractionManager& inter, PinCreator& creator,
         NotificationService& notifs, DatabaseManager& db)
    : feedManager(feed), profile(prof), boards(b),
      interactionManager(inter), pinCreator(creator),
      notifService(notifs), dbManager(db) {}

void CLI::displayBanner() {
    std::cout << "\n======================================================\n";
    std::cout << "  ✨ PIXORA — C++ Engine (Console & Server Edition) ✨\n";
    std::cout << "        Designed & Engineered by 10 Group Members       \n";
    std::cout << "======================================================\n";
}

void CLI::showMenu() {
    std::cout << "\n[1] 🖼️  View Pins Feed (" << feedManager.getCount() << " pins)\n";
    std::cout << "[2] 🔍 Search Pins (by title, tag, author, category)\n";
    std::cout << "[3] ➕ Create a New Pin\n";
    std::cout << "[4] ❤️  Like / 📌 Save a Pin\n";
    std::cout << "[5] 👤 View User Profile\n";
    std::cout << "[6] 📁 View Boards & Collections\n";
    std::cout << "[7] 🔔 View Recent Activity Notifications\n";
    std::cout << "[8] 💾 Save State to Disk (data/pins.json)\n";
    std::cout << "[0] 🚪 Exit CLI\n";
    std::cout << "Select an option: ";
}

void CLI::handleViewPins() {
    std::cout << "\n--- PIXORA MASONRY FEED ---\n";
    const auto& pins = feedManager.getAllPins();
    for (size_t i = 0; i < pins.size(); ++i) {
        const auto& p = pins[i];
        std::cout << "\n[" << (i + 1) << "] ID: " << p.getId() << "\n";
        std::cout << "    Title:    " << p.getTitle() << "\n";
        std::cout << "    Category: " << p.getCategory() << " | Board: " << p.getBoard() << "\n";
        std::cout << "    Author:   " << p.getAuthor().name << " (@" << p.getAuthor().handle << ")\n";
        std::cout << "    Stats:    ❤️ " << p.getLikes() << " likes | 📌 " << p.getSaves() << " saves\n";
        std::cout << "    Comments: " << p.getComments().size() << " discussion(s)\n";
        if (!p.getTags().empty()) {
            std::cout << "    Tags:     ";
            for (const auto& t : p.getTags()) std::cout << "#" << t << " ";
            std::cout << "\n";
        }
    }
}

void CLI::handleSearchPins() {
    std::cout << "\nEnter search term (keyword, category, tag): ";
    std::string query;
    std::cin.ignore();
    std::getline(std::cin, query);

    auto results = SearchEngine::search(feedManager.getAllPins(), query);
    std::cout << "\nFound " << results.size() << " result(s) matching '" << query << "':\n";
    for (size_t i = 0; i < results.size(); ++i) {
        const auto& p = results[i];
        std::cout << "  - [" << p.getId() << "] " << p.getTitle()
                  << " (" << p.getCategory() << ") by " << p.getAuthor().name << "\n";
    }
}

void CLI::handleCreatePin() {
    std::cin.ignore();
    std::string title, desc, img, cat, board, tags;
    std::cout << "\n--- CREATE A NEW PIN ---\n";
    std::cout << "Enter Title: ";
    std::getline(std::cin, title);
    std::cout << "Enter Description: ";
    std::getline(std::cin, desc);
    std::cout << "Enter Image URL: ";
    std::getline(std::cin, img);
    std::cout << "Enter Category (architecture/tech/fashion/nature): ";
    std::getline(std::cin, cat);
    std::cout << "Enter Board (e.g. Dream Architecture): ";
    std::getline(std::cin, board);
    std::cout << "Enter Tags (comma-separated): ";
    std::getline(std::cin, tags);

    Pin newPin;
    std::string err;
    if (pinCreator.createPin(title, desc, img, cat, board, tags, "", newPin, err)) {
        std::cout << "\n✅ Pin created successfully! ID: " << newPin.getId() << "\n";
        notifService.addNotification("Created pin: " + newPin.getTitle(), "create");
        dbManager.savePins(feedManager.getAllPins());
    } else {
        std::cout << "\n❌ Failed to create pin: " << err << "\n";
    }
}

void CLI::handleToggleLikeSave() {
    std::cout << "\nEnter Pin ID to interact with (e.g. pin-1): ";
    std::string id;
    std::cin >> id;

    Pin* p = feedManager.findPinById(id);
    if (!p) {
        std::cout << "Pin not found.\n";
        return;
    }

    std::cout << "Action for '" << p->getTitle() << "':\n";
    std::cout << "1. Toggle Like (Currently: " << (p->getIsLiked() ? "Liked" : "Not Liked") << ")\n";
    std::cout << "2. Toggle Save (Currently: " << (p->getIsSaved() ? "Saved" : "Not Saved") << ")\n";
    std::cout << "Choose action (1/2): ";
    int act;
    std::cin >> act;

    if (act == 1) {
        int likes = 0;
        bool isLiked = interactionManager.toggleLike(id, likes);
        std::cout << (isLiked ? "❤️ Liked!" : "🤍 Unliked.") << " New likes count: " << likes << "\n";
        notifService.addNotification((isLiked ? "Liked pin: " : "Unliked pin: ") + p->getTitle(), "like");
    } else if (act == 2) {
        int saves = 0;
        bool isSaved = interactionManager.toggleSave(id, p->getBoard(), saves);
        std::cout << (isSaved ? "📌 Saved!" : "Removed from saved.") << " Total saves: " << saves << "\n";
        notifService.addNotification((isSaved ? "Saved pin: " : "Unsaved pin: ") + p->getTitle(), "save");
    }
}

void CLI::handleViewProfile() {
    std::cout << "\n--- USER PROFILE ---\n";
    std::cout << "Name:      " << profile.getName() << " (@" << profile.getHandle() << ")\n";
    std::cout << "Title:     " << profile.getTitle() << "\n";
    std::cout << "Bio:       " << profile.getBio() << "\n";
    std::cout << "Location:  " << profile.getLocation() << "\n";
    std::cout << "Website:   " << profile.getWebsite() << "\n";
    std::cout << "Followers: " << profile.getFollowersCount() << " | Following: " << profile.getFollowingCount() << "\n";
    std::cout << "Saved:     " << profile.getSavesCount() << " pins\n";
}

void CLI::handleViewBoards() {
    std::cout << "\n--- USER BOARDS & COLLECTIONS ---\n";
    for (size_t i = 0; i < boards.size(); ++i) {
        const auto& b = boards[i];
        std::cout << "[" << (i + 1) << "] " << b.getTitle()
                  << " (" << (b.getIsPrivate() ? "🔒 Private" : "Public") << ")\n";
        std::cout << "    " << b.getDescription() << "\n";
        auto boardPins = feedManager.getPinsByBoard(b.getTitle());
        std::cout << "    Contains: " << boardPins.size() << " saved pin(s)\n";
    }
}

void CLI::handleViewNotifications() {
    std::cout << "\n--- RECENT ACTIVITY & NOTIFICATIONS ---\n";
    for (const auto& n : notifService.getNotifications()) {
        std::cout << "• [" << n.timestamp << "] " << n.message << "\n";
    }
}

void CLI::run() {
    displayBanner();
    int choice = -1;
    while (choice != 0) {
        showMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::string discard;
            std::cin >> discard;
            continue;
        }

        switch (choice) {
            case 1: handleViewPins(); break;
            case 2: handleSearchPins(); break;
            case 3: handleCreatePin(); break;
            case 4: handleToggleLikeSave(); break;
            case 5: handleViewProfile(); break;
            case 6: handleViewBoards(); break;
            case 7: handleViewNotifications(); break;
            case 8: {
                dbManager.savePins(feedManager.getAllPins());
                dbManager.saveBoards(boards);
                dbManager.saveProfile(profile);
                std::cout << "💾 State persisted to data/ directory successfully!\n";
                break;
            }
            case 0:
                std::cout << "\nThank you for exploring PIXORA C++ Engine!\n";
                break;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }
}

} // namespace Pixora
