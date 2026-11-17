#include "InteractionManager.hpp"
#include "Utils.hpp"

namespace Pixora {

InteractionManager::InteractionManager(FeedManager& feed, Profile& prof)
    : feedManager(feed), profile(prof) {
    followingHandles.insert("kasperlind");
    followingHandles.insert("oliverwild");
}

bool InteractionManager::toggleLike(const std::string& pinId, int& outLikes) {
    Pin* pin = feedManager.findPinById(pinId);
    if (!pin) return false;

    bool isLiked = pin->toggleLike();
    outLikes = pin->getLikes();
    return isLiked;
}

bool InteractionManager::toggleSave(const std::string& pinId, const std::string& boardName, int& outSaves) {
    Pin* pin = feedManager.findPinById(pinId);
    if (!pin) return false;

    bool isSaved = pin->toggleSave(boardName);
    outSaves = pin->getSaves();

    // Sync profile saves count
    profile.setSavesCount(static_cast<int>(feedManager.getSavedPins().size()));
    return isSaved;
}

bool InteractionManager::addComment(const std::string& pinId, const std::string& authorName,
                                    const std::string& avatar, const std::string& text,
                                    Comment& outComment) {
    Pin* pin = feedManager.findPinById(pinId);
    if (!pin) return false;

    std::string cleanText = Utils::trim(text);
    if (cleanText.empty()) return false;

    Comment c;
    c.id = Utils::generateId("c");
    c.userName = authorName.empty() ? profile.getName() : authorName;
    c.userAvatar = avatar.empty() ? profile.getAvatar() : avatar;
    c.text = cleanText;
    c.timestamp = "Just now";

    pin->addComment(c);
    outComment = c;
    return true;
}

bool InteractionManager::toggleFollow(const std::string& handle) {
    auto it = followingHandles.find(handle);
    bool nowFollowing = false;
    if (it != followingHandles.end()) {
        followingHandles.erase(it);
        nowFollowing = false;
    } else {
        followingHandles.insert(handle);
        nowFollowing = true;
    }
    profile.setFollowingCount(static_cast<int>(followingHandles.size()));
    return nowFollowing;
}

bool InteractionManager::isFollowing(const std::string& handle) const {
    return followingHandles.find(handle) != followingHandles.end();
}

} // namespace Pixora
