#include "Graph.h"

namespace pixora {

bool Graph::addUser(const std::string& username) {
    if (username.empty()) {
        return false;
    }
    if (users.find(username) != users.end()) {
        return false;
    }
    users.insert(username);
    followingMap[username]; // Ensure key exists
    followersMap[username]; // Ensure key exists
    return true;
}

bool Graph::hasUser(const std::string& username) const {
    return users.find(username) != users.end();
}

std::vector<std::string> Graph::getAllUsers() const {
    std::vector<std::string> result(users.begin(), users.end());
    std::sort(result.begin(), result.end());
    return result;
}

size_t Graph::getUserCount() const {
    return users.size();
}

size_t Graph::getTotalEdges() const {
    return totalFollowRelationships;
}

bool Graph::follow(const std::string& follower, const std::string& followee) {
    if (follower.empty() || followee.empty()) {
        return false;
    }
    // Prevent self-following
    if (follower == followee) {
        return false;
    }

    // Auto-register users if not present
    addUser(follower);
    addUser(followee);

    auto& fSet = followingMap[follower];
    // Check if relationship already exists
    if (fSet.find(followee) != fSet.end()) {
        return false;
    }

    // Add outgoing edge: follower -> followee
    fSet.insert(followee);

    // Add incoming edge: followee <- follower
    followersMap[followee].insert(follower);

    totalFollowRelationships++;
    return true;
}

bool Graph::unfollow(const std::string& follower, const std::string& followee) {
    if (!hasUser(follower) || !hasUser(followee)) {
        return false;
    }

    auto itFollowing = followingMap.find(follower);
    if (itFollowing == followingMap.end()) {
        return false;
    }

    auto edgeIt = itFollowing->second.find(followee);
    if (edgeIt == itFollowing->second.end()) {
        return false; // Was not following
    }

    // Remove from following
    itFollowing->second.erase(edgeIt);

    // Remove from followers
    auto itFollowers = followersMap.find(followee);
    if (itFollowers != followersMap.end()) {
        itFollowers->second.erase(follower);
    }

    if (totalFollowRelationships > 0) {
        totalFollowRelationships--;
    }
    return true;
}

bool Graph::isFollowing(const std::string& follower, const std::string& followee) const {
    if (!hasUser(follower) || !hasUser(followee)) {
        return false;
    }
    auto it = followingMap.find(follower);
    if (it == followingMap.end()) {
        return false;
    }
    return it->second.find(followee) != it->second.end();
}

std::vector<std::string> Graph::followers(const std::string& username) const {
    if (!hasUser(username)) {
        return {};
    }
    auto it = followersMap.find(username);
    if (it == followersMap.end()) {
        return {};
    }
    std::vector<std::string> result(it->second.begin(), it->second.end());
    std::sort(result.begin(), result.end());
    return result;
}

std::vector<std::string> Graph::following(const std::string& username) const {
    if (!hasUser(username)) {
        return {};
    }
    auto it = followingMap.find(username);
    if (it == followingMap.end()) {
        return {};
    }
    std::vector<std::string> result(it->second.begin(), it->second.end());
    std::sort(result.begin(), result.end());
    return result;
}

size_t Graph::getFollowersCount(const std::string& username) const {
    auto it = followersMap.find(username);
    if (it == followersMap.end()) {
        return 0;
    }
    return it->second.size();
}

size_t Graph::getFollowingCount(const std::string& username) const {
    auto it = followingMap.find(username);
    if (it == followingMap.end()) {
        return 0;
    }
    return it->second.size();
}

std::vector<std::string> Graph::mutual(const std::string& userA, const std::string& userB) const {
    if (!hasUser(userA) || !hasUser(userB)) {
        return {};
    }

    const auto& setA = followingMap.at(userA);
    const auto& setB = followingMap.at(userB);

    std::vector<std::string> result;

    // Iterate over the smaller set for O(min(|setA|, |setB|)) efficiency
    if (setA.size() <= setB.size()) {
        for (const auto& u : setA) {
            if (setB.find(u) != setB.end()) {
                result.push_back(u);
            }
        }
    } else {
        for (const auto& u : setB) {
            if (setA.find(u) != setA.end()) {
                result.push_back(u);
            }
        }
    }

    std::sort(result.begin(), result.end());
    return result;
}

std::vector<std::string> Graph::getMutualFollowers(const std::string& userA, const std::string& userB) const {
    if (!hasUser(userA) || !hasUser(userB)) {
        return {};
    }

    const auto& setA = followersMap.at(userA);
    const auto& setB = followersMap.at(userB);

    std::vector<std::string> result;

    if (setA.size() <= setB.size()) {
        for (const auto& u : setA) {
            if (setB.find(u) != setB.end()) {
                result.push_back(u);
            }
        }
    } else {
        for (const auto& u : setB) {
            if (setA.find(u) != setA.end()) {
                result.push_back(u);
            }
        }
    }

    std::sort(result.begin(), result.end());
    return result;
}

bool Graph::isMutualFollow(const std::string& userA, const std::string& userB) const {
    return isFollowing(userA, userB) && isFollowing(userB, userA);
}

std::vector<Suggestion> Graph::bfsSuggestions(const std::string& username, size_t limit, int maxDepth) const {
    if (!hasUser(username) || maxDepth < 2 || limit == 0) {
        return {};
    }

    const auto& myFollowing = followingMap.at(username);
    if (myFollowing.empty()) {
        return {}; // No seeds to perform BFS suggestion from
    }

    // Map to track candidate -> minimum BFS hop distance
    std::unordered_map<std::string, int> candidateDistance;

    // Standard BFS queue: (currentNode, currentDepth)
    std::queue<std::pair<std::string, int>> q;
    std::unordered_set<std::string> visited;

    visited.insert(username);

    // Seed BFS with level 1 (direct following)
    for (const auto& directFollow : myFollowing) {
        visited.insert(directFollow);
        q.push({directFollow, 1});
    }

    // BFS exploration
    while (!q.empty()) {
        auto [current, depth] = q.front();
        q.pop();

        if (depth >= maxDepth) {
            continue;
        }

        auto it = followingMap.find(current);
        if (it == followingMap.end()) {
            continue;
        }

        for (const auto& neighbor : it->second) {
            // Cannot recommend the user themselves or users already directly followed
            if (neighbor == username || myFollowing.find(neighbor) != myFollowing.end()) {
                continue;
            }

            int nextDepth = depth + 1;

            // Track minimum distance for candidate
            if (candidateDistance.find(neighbor) == candidateDistance.end()) {
                candidateDistance[neighbor] = nextDepth;
            } else {
                candidateDistance[neighbor] = std::min(candidateDistance[neighbor], nextDepth);
            }

            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push({neighbor, nextDepth});
            }
        }
    }

    // Build Suggestion objects with mutual connections calculation
    std::vector<Suggestion> suggestions;
    suggestions.reserve(candidateDistance.size());

    for (const auto& [candidate, dist] : candidateDistance) {
        Suggestion s;
        s.username = candidate;
        s.distance = dist;
        s.totalFollowers = getFollowersCount(candidate);

        // Find mutual connections: creators in myFollowing who also follow this candidate
        auto candFollowersIt = followersMap.find(candidate);
        if (candFollowersIt != followersMap.end()) {
            const auto& candFollowers = candFollowersIt->second;
            for (const auto& myFollow : myFollowing) {
                if (candFollowers.find(myFollow) != candFollowers.end()) {
                    s.mutualConnections.push_back(myFollow);
                }
            }
        }

        std::sort(s.mutualConnections.begin(), s.mutualConnections.end());
        s.mutualConnectionsCount = static_cast<int>(s.mutualConnections.size());

        suggestions.push_back(s);
    }

    // Sort according to suggestion ranking policy
    std::sort(suggestions.begin(), suggestions.end());

    // Truncate to requested limit
    if (suggestions.size() > limit) {
        suggestions.resize(limit);
    }

    return suggestions;
}

void Graph::printGraph() const {
    std::cout << "\n================ Pixora Social Network Graph ================\n";
    std::cout << "Total Users: " << getUserCount() 
              << " | Total Follow Relations: " << getTotalEdges() << "\n";
    std::cout << "-------------------------------------------------------------\n";

    auto allUsers = getAllUsers();
    if (allUsers.empty()) {
        std::cout << "  (Graph is empty)\n";
        std::cout << "=============================================================\n";
        return;
    }

    for (const auto& u : allUsers) {
        auto out = following(u);
        auto in = followers(u);

        std::cout << " " << std::left << std::setw(18) << ("@" + u)
                  << " [Following: " << std::setw(2) << out.size()
                  << " | Followers: " << std::setw(2) << in.size() << "] -> ";

        if (out.empty()) {
            std::cout << "none";
        } else {
            for (size_t i = 0; i < out.size(); ++i) {
                std::cout << "@" << out[i] << (i + 1 < out.size() ? ", " : "");
            }
        }
        std::cout << "\n";
    }
    std::cout << "=============================================================\n\n";
}

void Graph::clear() {
    users.clear();
    followingMap.clear();
    followersMap.clear();
    totalFollowRelationships = 0;
}

} // namespace pixora
