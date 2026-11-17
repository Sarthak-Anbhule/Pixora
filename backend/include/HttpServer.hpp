#ifndef PIXORA_HTTP_SERVER_HPP
#define PIXORA_HTTP_SERVER_HPP

#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include "FeedManager.hpp"
#include "Profile.hpp"
#include "Board.hpp"
#include "InteractionManager.hpp"
#include "PinCreator.hpp"
#include "NotificationService.hpp"
#include "DatabaseManager.hpp"

namespace Pixora {

class HttpServer {
private:
    int port;
    std::string webRoot;
    std::atomic<bool> isRunning{false};
    int serverSocket{-1};

    FeedManager& feedManager;
    Profile& profile;
    std::vector<Board>& boards;
    InteractionManager& interactionManager;
    PinCreator& pinCreator;
    NotificationService& notifService;
    DatabaseManager& dbManager;

    void handleClient(int clientSocket);
    std::string routeRequest(const std::string& method, const std::string& path, const std::string& body);
    std::string serveStaticFile(const std::string& filePath);
    std::string getContentType(const std::string& path);

public:
    HttpServer(int port, const std::string& webRoot,
               FeedManager& feed, Profile& prof, std::vector<Board>& b,
               InteractionManager& inter, PinCreator& creator,
               NotificationService& notifs, DatabaseManager& db);
    ~HttpServer();

    bool start();
    void stop();
};

} // namespace Pixora

#endif // PIXORA_HTTP_SERVER_HPP
