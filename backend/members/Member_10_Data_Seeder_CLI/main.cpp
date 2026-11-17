/**
 * PIXORA - Master C++ Application Bootstrap
 * Connects all 10 Member Subsystems into an integrated system.
 */

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include "FeedManager.hpp"
#include "Profile.hpp"
#include "Board.hpp"
#include "InteractionManager.hpp"
#include "PinCreator.hpp"
#include "SearchEngine.hpp"
#include "DatabaseManager.hpp"
#include "NotificationService.hpp"
#include "DataSeeder.hpp"
#include "CLI.hpp"
#include "HttpServer.hpp"

using namespace Pixora;

int main(int argc, char* argv[]) {
    std::cout << "[PIXORA C++] Initializing core data and storage...\n";

    // 1. Persistence & Database (Member 07)
    DatabaseManager dbManager("backend/data");

    // 2. Data seeding or loading from disk (Member 10)
    std::vector<Pin> pins;
    if (!dbManager.loadPins(pins)) {
        pins = DataSeeder::getInitialPins();
        dbManager.savePins(pins);
        std::cout << "[PIXORA C++] Seeded " << pins.size() << " initial pins.\n";
    }

    std::vector<Board> boards;
    if (!dbManager.loadBoards(boards)) {
        boards = DataSeeder::getInitialBoards();
        dbManager.saveBoards(boards);
    }

    Profile profile;
    if (!dbManager.loadProfile(profile)) {
        profile = DataSeeder::getInitialProfile();
        dbManager.saveProfile(profile);
    }

    // 3. Feed Manager (Member 02)
    FeedManager feedManager;
    feedManager.setPins(pins);

    // 4. Social Interactions (Member 03)
    InteractionManager interactionManager(feedManager, profile);

    // 5. Pin Ingestion (Member 04)
    PinCreator pinCreator(feedManager, profile);

    // 6. Notifications & Analytics (Member 08)
    NotificationService notifService;

    // Determine Run Mode
    std::string mode = "server"; // Default mode
    int port = 8080;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--cli") {
            mode = "cli";
        } else if (arg == "--server") {
            mode = "server";
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                port = std::stoi(argv[++i]);
            }
        } else if (arg == "--both") {
            mode = "both";
        } else if (arg == "--help" || arg == "-h") {
            std::cout << "PIXORA C++ Engine Usage:\n";
            std::cout << "  ./pixora --server [port]   Start C++ Web Server (default port: 8080)\n";
            std::cout << "  ./pixora --cli             Launch Interactive Terminal Menu\n";
            std::cout << "  ./pixora --both            Run both Web Server and Terminal Menu\n";
            return 0;
        }
    }

    if (mode == "cli") {
        CLI cli(feedManager, profile, boards, interactionManager, pinCreator, notifService, dbManager);
        cli.run();
    } else if (mode == "both") {
        std::thread serverThread([&]() {
            HttpServer server(port, "frontend", feedManager, profile, boards, interactionManager, pinCreator, notifService, dbManager);
            server.start();
        });
        serverThread.detach();

        CLI cli(feedManager, profile, boards, interactionManager, pinCreator, notifService, dbManager);
        cli.run();
    } else {
        // Default: Web Server
        HttpServer server(port, "frontend", feedManager, profile, boards, interactionManager, pinCreator, notifService, dbManager);
        server.start();
    }

    return 0;
}
