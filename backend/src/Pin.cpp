#include "Pin.hpp"
#include "Utils.hpp"
#include "JsonHelper.hpp"
#include <sstream>

namespace Pixora {

std::string Author::toJson() const {
    std::ostringstream ss;
    ss << "{"
       << "\"name\":\"" << Utils::escapeJson(name) << "\","
       << "\"handle\":\"" << Utils::escapeJson(handle) << "\","
       << "\"avatar\":\"" << Utils::escapeJson(avatar) << "\","
       << "\"verified\":" << (verified ? "true" : "false") << ","
       << "\"followers\":" << followers
       << "}";
    return ss.str();
}

std::string Comment::toJson() const {
    std::ostringstream ss;
    ss << "{"
       << "\"id\":\"" << Utils::escapeJson(id) << "\","
       << "\"user\":{\"name\":\"" << Utils::escapeJson(userName) << "\",\"avatar\":\"" << Utils::escapeJson(userAvatar) << "\"},"
       << "\"text\":\"" << Utils::escapeJson(text) << "\","
       << "\"timestamp\":\"" << Utils::escapeJson(timestamp) << "\""
       << "}";
    return ss.str();
}

Pin::Pin() : aspectRatio("medium"), height(480), likes(0), saves(0), isLiked(false), isSaved(false) {
    createdAt = Utils::getCurrentDate();
}

Pin::Pin(const std::string& id, const std::string& title, const std::string& description,
         const std::string& imageUrl, const std::string& category, const std::string& board,
         const Author& author)
    : id(id), title(title), description(description), imageUrl(imageUrl),
      aspectRatio("medium"), height(480), category(category), board(board),
      likes(0), saves(0), isLiked(false), isSaved(false), author(author) {
    createdAt = Utils::getCurrentDate();
}

bool Pin::toggleLike() {
    isLiked = !isLiked;
    if (isLiked) {
        likes++;
    } else {
        if (likes > 0) likes--;
    }
    return isLiked;
}

bool Pin::toggleSave(const std::string& targetBoard) {
    isSaved = !isSaved;
    if (isSaved) {
        saves++;
        if (!targetBoard.empty()) {
            board = targetBoard;
        }
    } else {
        if (saves > 0) saves--;
    }
    return isSaved;
}

void Pin::addComment(const Comment& comment) {
    comments.push_back(comment);
}

std::string Pin::toJson() const {
    std::ostringstream ss;
    ss << "{"
       << "\"id\":\"" << Utils::escapeJson(id) << "\","
       << "\"title\":\"" << Utils::escapeJson(title) << "\","
       << "\"description\":\"" << Utils::escapeJson(description) << "\","
       << "\"imageUrl\":\"" << Utils::escapeJson(imageUrl) << "\","
       << "\"aspectRatio\":\"" << Utils::escapeJson(aspectRatio) << "\","
       << "\"height\":" << height << ","
       << "\"category\":\"" << Utils::escapeJson(category) << "\","
       << "\"board\":\"" << Utils::escapeJson(board) << "\","
       << "\"sourceUrl\":\"" << Utils::escapeJson(sourceUrl) << "\","
       << "\"likes\":" << likes << ","
       << "\"saves\":" << saves << ","
       << "\"isLiked\":" << (isLiked ? "true" : "false") << ","
       << "\"isSaved\":" << (isSaved ? "true" : "false") << ","
       << "\"createdAt\":\"" << Utils::escapeJson(createdAt) << "\","
       << "\"author\":" << author.toJson() << ",";

    // Tags array
    ss << "\"tags\":[";
    for (size_t i = 0; i < tags.size(); ++i) {
        ss << "\"" << Utils::escapeJson(tags[i]) << "\"";
        if (i + 1 < tags.size()) ss << ",";
    }
    ss << "],";

    // Comments array
    ss << "\"comments\":[";
    for (size_t i = 0; i < comments.size(); ++i) {
        ss << comments[i].toJson();
        if (i + 1 < comments.size()) ss << ",";
    }
    ss << "]";

    ss << "}";
    return ss.str();
}

Pin Pin::fromJson(const std::string& json) {
    Pin p;
    p.id = JsonHelper::getString(json, "id");
    p.title = JsonHelper::getString(json, "title");
    p.description = JsonHelper::getString(json, "description");
    p.imageUrl = JsonHelper::getString(json, "imageUrl");
    p.aspectRatio = JsonHelper::getString(json, "aspectRatio", "medium");
    p.height = JsonHelper::getInt(json, "height", 480);
    p.category = JsonHelper::getString(json, "category", "art-design");
    p.board = JsonHelper::getString(json, "board", "Creative Inspiration");
    p.sourceUrl = JsonHelper::getString(json, "sourceUrl");
    p.likes = JsonHelper::getInt(json, "likes", 0);
    p.saves = JsonHelper::getInt(json, "saves", 0);
    p.isLiked = JsonHelper::getBool(json, "isLiked", false);
    p.isSaved = JsonHelper::getBool(json, "isSaved", false);
    p.createdAt = JsonHelper::getString(json, "createdAt", Utils::getCurrentDate());
    p.tags = JsonHelper::getArrayOfStrings(json, "tags");

    // Author
    p.author.name = JsonHelper::getString(json, "name", "Elena Vance");
    p.author.handle = JsonHelper::getString(json, "handle", "elenavance");
    p.author.avatar = JsonHelper::getString(json, "avatar", "https://images.unsplash.com/photo-1534528741775-53994a69daeb?auto=format&fit=crop&w=400&q=80");
    p.author.verified = JsonHelper::getBool(json, "verified", true);
    p.author.followers = JsonHelper::getInt(json, "followers", 1840);

    return p;
}

} // namespace Pixora
