#ifndef PIXORA_DATABASE_MANAGER_HPP
#define PIXORA_DATABASE_MANAGER_HPP

#include <string>
#include <vector>
#include "Pin.hpp"
#include "Board.hpp"
#include "Profile.hpp"

namespace Pixora {

class DatabaseManager {
private:
    std::string dataDir;
    std::string pinsFile;
    std::string boardsFile;
    std::string profileFile;

    bool ensureDirectoryExists(const std::string& path);

public:
    DatabaseManager(const std::string& directory = "data");

    bool savePins(const std::vector<Pin>& pins);
    bool loadPins(std::vector<Pin>& outPins);

    bool saveBoards(const std::vector<Board>& boards);
    bool loadBoards(std::vector<Board>& outBoards);

    bool saveProfile(const Profile& profile);
    bool loadProfile(Profile& outProfile);

    bool fileExists(const std::string& filename) const;
};

} // namespace Pixora

#endif // PIXORA_DATABASE_MANAGER_HPP
