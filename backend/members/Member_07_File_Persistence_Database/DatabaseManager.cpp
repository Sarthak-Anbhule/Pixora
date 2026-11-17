#include "DatabaseManager.hpp"
#include "Utils.hpp"
#include <fstream>
#include <sstream>
#include <sys/stat.h>

namespace Pixora {

DatabaseManager::DatabaseManager(const std::string& directory)
    : dataDir(directory) {
    ensureDirectoryExists(dataDir);
    pinsFile = dataDir + "/pins.json";
    boardsFile = dataDir + "/boards.json";
    profileFile = dataDir + "/profile.json";
}

bool DatabaseManager::ensureDirectoryExists(const std::string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
        #ifdef _WIN32
            return mkdir(path.c_str()) == 0;
        #else
            return mkdir(path.c_str(), 0755) == 0;
        #endif
    }
    return (info.st_mode & S_IFDIR) != 0;
}

bool DatabaseManager::fileExists(const std::string& filename) const {
    std::ifstream f(filename.c_str());
    return f.good();
}

bool DatabaseManager::savePins(const std::vector<Pin>& pins) {
    std::ofstream out(pinsFile);
    if (!out.is_open()) return false;

    out << "[\n";
    for (size_t i = 0; i < pins.size(); ++i) {
        out << pins[i].toJson();
        if (i + 1 < pins.size()) out << ",\n";
    }
    out << "\n]";
    out.close();
    return true;
}

bool DatabaseManager::loadPins(std::vector<Pin>& outPins) {
    std::ifstream in(pinsFile);
    if (!in.is_open()) return false;

    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string content = buffer.str();
    in.close();

    // Parse array of pins
    outPins.clear();
    size_t i = 0;
    while (i < content.length()) {
        size_t start = content.find('{', i);
        if (start == std::string::npos) break;

        // Find matching closing brace
        int depth = 0;
        size_t end = start;
        bool inStr = false;
        while (end < content.length()) {
            char c = content[end];
            if (c == '"' && (end == 0 || content[end - 1] != '\\')) {
                inStr = !inStr;
            } else if (!inStr) {
                if (c == '{') depth++;
                else if (c == '}') {
                    depth--;
                    if (depth == 0) break;
                }
            }
            end++;
        }

        if (end < content.length()) {
            std::string objJson = content.substr(start, end - start + 1);
            outPins.push_back(Pin::fromJson(objJson));
            i = end + 1;
        } else {
            break;
        }
    }
    return !outPins.empty();
}

bool DatabaseManager::saveBoards(const std::vector<Board>& boards) {
    std::ofstream out(boardsFile);
    if (!out.is_open()) return false;

    out << "[\n";
    for (size_t i = 0; i < boards.size(); ++i) {
        out << boards[i].toJson();
        if (i + 1 < boards.size()) out << ",\n";
    }
    out << "\n]";
    out.close();
    return true;
}

bool DatabaseManager::loadBoards(std::vector<Board>& outBoards) {
    std::ifstream in(boardsFile);
    if (!in.is_open()) return false;

    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string content = buffer.str();
    in.close();

    outBoards.clear();
    size_t i = 0;
    while (i < content.length()) {
        size_t start = content.find('{', i);
        if (start == std::string::npos) break;

        size_t end = content.find('}', start);
        if (end == std::string::npos) break;

        std::string objJson = content.substr(start, end - start + 1);
        outBoards.push_back(Board::fromJson(objJson));
        i = end + 1;
    }
    return !outBoards.empty();
}

bool DatabaseManager::saveProfile(const Profile& profile) {
    std::ofstream out(profileFile);
    if (!out.is_open()) return false;
    out << profile.toJson();
    out.close();
    return true;
}

bool DatabaseManager::loadProfile(Profile& outProfile) {
    std::ifstream in(profileFile);
    if (!in.is_open()) return false;

    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string content = buffer.str();
    in.close();

    outProfile = Profile::fromJson(content);
    return true;
}

} // namespace Pixora
