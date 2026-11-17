#ifndef PIXORA_INTERACTION_MANAGER_HPP
#define PIXORA_INTERACTION_MANAGER_HPP

#include <string>
#include <set>
#include "FeedManager.hpp"
#include "Profile.hpp"

namespace Pixora {

class InteractionManager {
private:
    FeedManager& feedManager;
    Profile& profile;
    std::set<std::string> followingHandles;

public:
    InteractionManager(FeedManager& feed, Profile& prof);

    bool toggleLike(const std::string& pinId, int& outLikes);
    bool toggleSave(const std::string& pinId, const std::string& boardName, int& outSaves);
    bool addComment(const std::string& pinId, const std::string& authorName, const std::string& avatar, const std::string& text, Comment& outComment);
    bool toggleFollow(const std::string& handle);
    bool isFollowing(const std::string& handle) const;
    const std::set<std::string>& getFollowingHandles() const { return followingHandles; }
};

} // namespace Pixora

#endif // PIXORA_INTERACTION_MANAGER_HPP
