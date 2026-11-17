#ifndef PIXORA_CLI_HPP
#define PIXORA_CLI_HPP

#include "FeedManager.hpp"
#include "Profile.hpp"
#include "Board.hpp"
#include "InteractionManager.hpp"
#include "PinCreator.hpp"
#include "NotificationService.hpp"
#include "DatabaseManager.hpp"

namespace Pixora {

class CLI {
private:
    FeedManager& feedManager;
    Profile& profile;
    std::vector<Board>& boards;
    InteractionManager& interactionManager;
    PinCreator& pinCreator;
    NotificationService& notifService;
    DatabaseManager& dbManager;

    void displayBanner();
    void showMenu();
    void handleViewPins();
    void handleSearchPins();
    void handleCreatePin();
    void handleToggleLikeSave();
    void handleViewProfile();
    void handleViewBoards();
    void handleViewNotifications();

public:
    CLI(FeedManager& feed, Profile& prof, std::vector<Board>& b,
        InteractionManager& inter, PinCreator& creator,
        NotificationService& notifs, DatabaseManager& db);

    void run();
};

} // namespace Pixora

#endif // PIXORA_CLI_HPP
