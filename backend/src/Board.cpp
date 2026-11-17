#include "Board.hpp"
#include "Utils.hpp"
#include "JsonHelper.hpp"
#include <sstream>

namespace Pixora {

Board::Board() : pinCount(0), isPrivate(false) {
    createdAt = Utils::getCurrentDate();
}

Board::Board(const std::string& id, const std::string& title, const std::string& description,
             const std::string& coverImage, int pinCount, bool isPrivate)
    : id(id), title(title), description(description), coverImage(coverImage),
      pinCount(pinCount), isPrivate(isPrivate) {
    createdAt = Utils::getCurrentDate();
}

std::string Board::toJson() const {
    std::ostringstream ss;
    ss << "{"
       << "\"id\":\"" << Utils::escapeJson(id) << "\","
       << "\"title\":\"" << Utils::escapeJson(title) << "\","
       << "\"description\":\"" << Utils::escapeJson(description) << "\","
       << "\"coverImage\":\"" << Utils::escapeJson(coverImage) << "\","
       << "\"pinCount\":" << pinCount << ","
       << "\"isPrivate\":" << (isPrivate ? "true" : "false") << ","
       << "\"createdAt\":\"" << Utils::escapeJson(createdAt) << "\""
       << "}";
    return ss.str();
}

Board Board::fromJson(const std::string& json) {
    Board b;
    b.id = JsonHelper::getString(json, "id");
    b.title = JsonHelper::getString(json, "title");
    b.description = JsonHelper::getString(json, "description");
    b.coverImage = JsonHelper::getString(json, "coverImage", "https://images.unsplash.com/photo-1600585154340-be6161a56a0c?auto=format&fit=crop&w=800&q=80");
    b.pinCount = JsonHelper::getInt(json, "pinCount", 0);
    b.isPrivate = JsonHelper::getBool(json, "isPrivate", false);
    b.createdAt = JsonHelper::getString(json, "createdAt", Utils::getCurrentDate());
    return b;
}

} // namespace Pixora
