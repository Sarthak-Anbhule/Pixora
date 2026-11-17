#include "HttpServer.hpp"
#include "SearchEngine.hpp"
#include "Utils.hpp"
#include "JsonHelper.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>

namespace Pixora {

HttpServer::HttpServer(int port, const std::string& webRoot,
                       FeedManager& feed, Profile& prof, std::vector<Board>& b,
                       InteractionManager& inter, PinCreator& creator,
                       NotificationService& notifs, DatabaseManager& db)
    : port(port), webRoot(webRoot),
      feedManager(feed), profile(prof), boards(b),
      interactionManager(inter), pinCreator(creator),
      notifService(notifs), dbManager(db) {}

HttpServer::~HttpServer() {
    stop();
}

void HttpServer::stop() {
    if (isRunning) {
        isRunning = false;
        if (serverSocket >= 0) {
            close(serverSocket);
            serverSocket = -1;
        }
    }
}

std::string HttpServer::getContentType(const std::string& path) {
    if (path.rfind(".html") != std::string::npos) return "text/html; charset=utf-8";
    if (path.rfind(".css") != std::string::npos) return "text/css; charset=utf-8";
    if (path.rfind(".js") != std::string::npos) return "application/javascript; charset=utf-8";
    if (path.rfind(".json") != std::string::npos) return "application/json; charset=utf-8";
    if (path.rfind(".svg") != std::string::npos) return "image/svg+xml";
    if (path.rfind(".png") != std::string::npos) return "image/png";
    if (path.rfind(".jpg") != std::string::npos || path.rfind(".jpeg") != std::string::npos) return "image/jpeg";
    return "text/plain";
}

std::string HttpServer::serveStaticFile(const std::string& filePath) {
    std::string fullPath = webRoot + filePath;
    if (filePath == "/" || filePath.empty()) fullPath = webRoot + "/index.html";

    std::ifstream file(fullPath, std::ios::binary);
    if (!file.is_open()) {
        std::string notFound = "{\"error\": \"File not found\"}";
        return "HTTP/1.1 404 Not Found\r\nContent-Type: application/json\r\nContent-Length: " +
               std::to_string(notFound.length()) + "\r\nAccess-Control-Allow-Origin: *\r\n\r\n" + notFound;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();
    file.close();

    std::string contentType = getContentType(fullPath);
    return "HTTP/1.1 200 OK\r\nContent-Type: " + contentType +
           "\r\nContent-Length: " + std::to_string(content.length()) +
           "\r\nAccess-Control-Allow-Origin: *\r\n\r\n" + content;
}

std::string HttpServer::routeRequest(const std::string& method, const std::string& path, const std::string& body) {
    // CORS Preflight
    if (method == "OPTIONS") {
        return "HTTP/1.1 204 No Content\r\n"
               "Access-Control-Allow-Origin: *\r\n"
               "Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS\r\n"
               "Access-Control-Allow-Headers: Content-Type\r\n\r\n";
    }

    // API Routing
    if (path.rfind("/api/pins", 0) == 0) {
        if (method == "GET") {
            // Check for /api/pins/:id
            if (path.length() > 10 && path[9] == '/') {
                std::string pinId = path.substr(10);
                Pin* p = feedManager.findPinById(pinId);
                if (p) {
                    std::string json = p->toJson();
                    return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " +
                           std::to_string(json.length()) + "\r\n\r\n" + json;
                }
                std::string err = "{\"error\":\"Pin not found\"}";
                return "HTTP/1.1 404 Not Found\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " +
                       std::to_string(err.length()) + "\r\n\r\n" + err;
            }

            // GET all pins
            std::string json = feedManager.allPinsToJson();
            return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " +
                   std::to_string(json.length()) + "\r\n\r\n" + json;
        }

        if (method == "POST") {
            // Check for actions: /api/pins/:id/like, /api/pins/:id/save, /api/pins/:id/comment
            size_t slashPos = path.find('/', 10);
            if (slashPos != std::string::npos) {
                std::string pinId = path.substr(10, slashPos - 10);
                std::string action = path.substr(slashPos + 1);

                if (action == "like") {
                    int likes = 0;
                    bool isLiked = interactionManager.toggleLike(pinId, likes);
                    std::string res = "{\"isLiked\":" + std::string(isLiked ? "true" : "false") + ",\"likes\":" + std::to_string(likes) + "}";
                    return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " +
                           std::to_string(res.length()) + "\r\n\r\n" + res;
                }

                if (action == "save") {
                    std::string targetBoard = JsonHelper::getString(body, "board", "Creative Inspiration");
                    int saves = 0;
                    bool isSaved = interactionManager.toggleSave(pinId, targetBoard, saves);
                    std::string res = "{\"isSaved\":" + std::string(isSaved ? "true" : "false") + ",\"saves\":" + std::to_string(saves) + "}";
                    return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " +
                           std::to_string(res.length()) + "\r\n\r\n" + res;
                }

                if (action == "comment") {
                    std::string text = JsonHelper::getString(body, "text");
                    Comment c;
                    if (interactionManager.addComment(pinId, profile.getName(), profile.getAvatar(), text, c)) {
                        std::string res = c.toJson();
                        return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " +
                               std::to_string(res.length()) + "\r\n\r\n" + res;
                    }
                    std::string err = "{\"error\":\"Empty comment text\"}";
                    return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " +
                           std::to_string(err.length()) + "\r\n\r\n" + err;
                }
            }

            // Create pin
            Pin newPin;
            std::string err;
            if (pinCreator.createPinFromJson(body, newPin, err)) {
                dbManager.savePins(feedManager.getAllPins());
                std::string res = newPin.toJson();
                return "HTTP/1.1 201 Created\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " +
                       std::to_string(res.length()) + "\r\n\r\n" + res;
            }
            std::string errJson = "{\"error\":\"" + err + "\"}";
            return "HTTP/1.1 400 Bad Request\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " +
                   std::to_string(errJson.length()) + "\r\n\r\n" + errJson;
        }
    }

    // Profile API
    if (path.rfind("/api/profile", 0) == 0) {
        if (method == "GET") {
            std::string json = profile.toJson();
            return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " +
                   std::to_string(json.length()) + "\r\n\r\n" + json;
        }
        if (method == "POST") {
            profile = Profile::fromJson(body);
            dbManager.saveProfile(profile);
            std::string json = profile.toJson();
            return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " +
                   std::to_string(json.length()) + "\r\n\r\n" + json;
        }
    }

    // Boards API
    if (path.rfind("/api/boards", 0) == 0) {
        if (method == "GET") {
            std::ostringstream ss;
            ss << "[";
            for (size_t i = 0; i < boards.size(); ++i) {
                ss << boards[i].toJson();
                if (i + 1 < boards.size()) ss << ",";
            }
            ss << "]";
            std::string json = ss.str();
            return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " +
                   std::to_string(json.length()) + "\r\n\r\n" + json;
        }
        if (method == "POST") {
            Board newB = Board::fromJson(body);
            if (newB.getId().empty()) newB.setId(Utils::generateId("board"));
            boards.push_back(newB);
            dbManager.saveBoards(boards);
            std::string json = newB.toJson();
            return "HTTP/1.1 201 Created\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " +
                   std::to_string(json.length()) + "\r\n\r\n" + json;
        }
    }

    // Notifications API
    if (path.rfind("/api/notifications", 0) == 0) {
        std::string json = notifService.toJson();
        return "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\nContent-Length: " +
               std::to_string(json.length()) + "\r\n\r\n" + json;
    }

    // Fallback to static file serving from frontend directory
    return serveStaticFile(path);
}

void HttpServer::handleClient(int clientSocket) {
    char buffer[40960];
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);

    if (bytesRead <= 0) {
        close(clientSocket);
        return;
    }

    std::string request(buffer, bytesRead);
    std::istringstream reqStream(request);
    std::string method, path, proto;
    reqStream >> method >> path >> proto;

    // Extract body if POST
    std::string body = "";
    size_t bodyPos = request.find("\r\n\r\n");
    if (bodyPos != std::string::npos) {
        body = request.substr(bodyPos + 4);
    }

    std::string response = routeRequest(method, path, body);
    write(clientSocket, response.c_str(), response.length());
    close(clientSocket);
}

bool HttpServer::start() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Failed to create socket.\n";
        return false;
    }

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to bind to port " << port << ".\n";
        close(serverSocket);
        return false;
    }

    if (listen(serverSocket, 20) < 0) {
        std::cerr << "Failed to listen on socket.\n";
        close(serverSocket);
        return false;
    }

    isRunning = true;
    std::cout << "\n======================================================\n";
    std::cout << "  🚀 PIXORA C++ HTTP Server Live on http://localhost:" << port << "\n";
    std::cout << "  Serving Web UI & REST API seamlessly from C++!\n";
    std::cout << "======================================================\n\n";

    while (isRunning) {
        sockaddr_in clientAddr{};
        socklen_t clientLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientLen);

        if (clientSocket < 0) {
            if (!isRunning) break;
            continue;
        }

        // Spawn detached thread to handle request
        std::thread([this, clientSocket]() {
            handleClient(clientSocket);
        }).detach();
    }

    return true;
}

} // namespace Pixora
