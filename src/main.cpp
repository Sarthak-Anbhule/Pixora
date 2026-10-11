#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "Graph.h"

// ANSI Color Codes for terminal UI
namespace Color {
    const std::string RESET   = "\033[0m";
    const std::string BOLD    = "\033[1m";
    const std::string RED     = "\033[31m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string BLUE    = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN    = "\033[36m";
    const std::string WHITE   = "\033[37m";
}

void printBanner() {
    std::cout << Color::MAGENTA << Color::BOLD << R"(
  ____  _                      
 |  _ \(_)_  _____  _ __ __ _  
 | |_) | \ \/ / _ \| '__/ _` | 
 |  __/| |>  < (_) | | | (_| | 
 |_|   |_/_/\_\___/|_|  \__,_|  Social Graph Engine [Pinterest Architecture]
)" << Color::RESET << "\n";
    std::cout << Color::CYAN << " Connected Graph Module: Follow / Mutuals / BFS Recommender\n" << Color::RESET;
}

void loadSampleData(pixora::Graph& graph) {
    graph.clear();

    // Creative creators on Pixora
    graph.follow("aesthetic_vibes", "craft_queen");
    graph.follow("aesthetic_vibes", "cozy_home");
    graph.follow("aesthetic_vibes", "pixel_artist");

    graph.follow("craft_queen", "aesthetic_vibes"); // Mutual!
    graph.follow("craft_queen", "plant_whisperer");
    graph.follow("craft_queen", "minimalist_space");

    graph.follow("cozy_home", "minimalist_space");
    graph.follow("cozy_home", "plant_whisperer");
    graph.follow("cozy_home", "gourmet_kitchen");

    graph.follow("pixel_artist", "film_colors");
    graph.follow("pixel_artist", "minimalist_space");

    graph.follow("travel_diaries", "film_colors");
    graph.follow("travel_diaries", "aesthetic_vibes");

    graph.follow("gourmet_kitchen", "cozy_home");
    graph.follow("plant_whisperer", "cozy_home");
    graph.follow("fashion_daily", "aesthetic_vibes");
    graph.follow("fashion_daily", "craft_queen");

    std::cout << Color::GREEN << "✓ Loaded Pinterest-style seed network with "
              << graph.getUserCount() << " creators and " 
              << graph.getTotalEdges() << " follow relationships!\n" << Color::RESET;
}

void handleFollow(pixora::Graph& graph) {
    std::string follower, followee;
    std::cout << Color::BOLD << "\n--- Follow a Creator ---\n" << Color::RESET;
    std::cout << "Enter follower handle (e.g. aesthetic_vibes): ";
    std::cin >> follower;
    std::cout << "Enter creator to follow (e.g. plant_whisperer): ";
    std::cin >> followee;

    if (follower == followee) {
        std::cout << Color::RED << "✖ Error: A user cannot follow themselves!\n" << Color::RESET;
        return;
    }

    if (graph.follow(follower, followee)) {
        std::cout << Color::GREEN << "✓ Success: @" << follower << " is now following @" << followee << "!\n" << Color::RESET;
        if (graph.isMutualFollow(follower, followee)) {
            std::cout << Color::MAGENTA << "★ It's a match! @" << follower << " and @" << followee << " are now mutuals!\n" << Color::RESET;
        }
    } else {
        std::cout << Color::YELLOW << "⚠ Info: @" << follower << " was already following @" << followee << ".\n" << Color::RESET;
    }
}

void handleUnfollow(pixora::Graph& graph) {
    std::string follower, followee;
    std::cout << Color::BOLD << "\n--- Unfollow a Creator ---\n" << Color::RESET;
    std::cout << "Enter follower handle: ";
    std::cin >> follower;
    std::cout << "Enter creator to unfollow: ";
    std::cin >> followee;

    if (graph.unfollow(follower, followee)) {
        std::cout << Color::GREEN << "✓ Success: @" << follower << " unfollowed @" << followee << ".\n" << Color::RESET;
    } else {
        std::cout << Color::RED << "✖ Error: @" << follower << " does not follow @" << followee << ".\n" << Color::RESET;
    }
}

void handleFollowers(const pixora::Graph& graph) {
    std::string username;
    std::cout << Color::BOLD << "\n--- View Followers ---\n" << Color::RESET;
    std::cout << "Enter username: ";
    std::cin >> username;

    if (!graph.hasUser(username)) {
        std::cout << Color::RED << "✖ User @" << username << " does not exist.\n" << Color::RESET;
        return;
    }

    auto list = graph.followers(username);
    std::cout << Color::CYAN << "\nFollowers of @" << username << " (" << list.size() << "):\n" << Color::RESET;
    if (list.empty()) {
        std::cout << "  No followers yet.\n";
    } else {
        for (const auto& u : list) {
            std::cout << "  • @" << u;
            if (graph.isMutualFollow(username, u)) {
                std::cout << Color::MAGENTA << " [Mutual]" << Color::RESET;
            }
            std::cout << "\n";
        }
    }
}

void handleFollowing(const pixora::Graph& graph) {
    std::string username;
    std::cout << Color::BOLD << "\n--- View Following ---\n" << Color::RESET;
    std::cout << "Enter username: ";
    std::cin >> username;

    if (!graph.hasUser(username)) {
        std::cout << Color::RED << "✖ User @" << username << " does not exist.\n" << Color::RESET;
        return;
    }

    auto list = graph.following(username);
    std::cout << Color::CYAN << "\nCreators @" << username << " follows (" << list.size() << "):\n" << Color::RESET;
    if (list.empty()) {
        std::cout << "  Not following anyone yet.\n";
    } else {
        for (const auto& u : list) {
            std::cout << "  • @" << u;
            if (graph.isMutualFollow(username, u)) {
                std::cout << Color::MAGENTA << " [Mutual]" << Color::RESET;
            }
            std::cout << "\n";
        }
    }
}

void handleMutual(const pixora::Graph& graph) {
    std::string userA, userB;
    std::cout << Color::BOLD << "\n--- Mutual Connections Explorer ---\n" << Color::RESET;
    std::cout << "Enter first user: ";
    std::cin >> userA;
    std::cout << "Enter second user: ";
    std::cin >> userB;

    if (!graph.hasUser(userA) || !graph.hasUser(userB)) {
        std::cout << Color::RED << "✖ One or both users do not exist.\n" << Color::RESET;
        return;
    }

    // 1. Are they mutuals? (Bidirectional follow)
    bool areMutuals = graph.isMutualFollow(userA, userB);
    std::cout << "\nStatus: @" << userA << " and @" << userB << " are "
              << (areMutuals ? (Color::GREEN + "MUTUAL FOLLOWERS (they follow each other!)" + Color::RESET) 
                             : (Color::YELLOW + "NOT mutual followers" + Color::RESET)) << "\n";

    // 2. Common followings (accounts they both follow)
    auto commonFollowings = graph.mutual(userA, userB);
    std::cout << Color::CYAN << "Common creators they BOTH follow (" << commonFollowings.size() << "):\n" << Color::RESET;
    if (commonFollowings.empty()) {
        std::cout << "  None in common.\n";
    } else {
        for (const auto& u : commonFollowings) {
            std::cout << "  • @" << u << "\n";
        }
    }

    // 3. Common followers (users who follow both)
    auto commonFollowers = graph.getMutualFollowers(userA, userB);
    std::cout << Color::CYAN << "Users who follow BOTH of them (" << commonFollowers.size() << "):\n" << Color::RESET;
    if (commonFollowers.empty()) {
        std::cout << "  None in common.\n";
    } else {
        for (const auto& u : commonFollowers) {
            std::cout << "  • @" << u << "\n";
        }
    }
}

void handleBFSSuggestions(const pixora::Graph& graph) {
    std::string username;
    int limit = 5;
    int maxDepth = 2;

    std::cout << Color::BOLD << "\n--- BFS Personalized Recommendations (\"Suggested for You\") ---\n" << Color::RESET;
    std::cout << "Enter username: ";
    std::cin >> username;

    if (!graph.hasUser(username)) {
        std::cout << Color::RED << "✖ User @" << username << " does not exist.\n" << Color::RESET;
        return;
    }

    std::cout << "Enter max recommendations to show [default 5]: ";
    if (!(std::cin >> limit) || limit <= 0) {
        limit = 5;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Enter BFS exploration depth (2 = friends of friends, 3 = 3rd degree) [default 2]: ";
    if (!(std::cin >> maxDepth) || maxDepth < 2) {
        maxDepth = 2;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    auto suggestions = graph.bfsSuggestions(username, limit, maxDepth);

    std::cout << Color::CYAN << "\nRecommended creators for @" << username << ":\n" << Color::RESET;
    if (suggestions.empty()) {
        std::cout << "  No suggestions found. Try following more creators to seed recommendations!\n";
    } else {
        int rank = 1;
        for (const auto& s : suggestions) {
            std::cout << Color::BOLD << " " << rank++ << ". @" << s.username << Color::RESET
                      << " (BFS Degree: " << s.distance 
                      << ", Total Followers: " << s.totalFollowers << ")\n";

            if (s.mutualConnectionsCount > 0) {
                std::cout << "    " << Color::GREEN << "Followed by " << s.mutualConnectionsCount 
                          << " creators you follow: " << Color::RESET;
                for (size_t i = 0; i < s.mutualConnections.size(); ++i) {
                    std::cout << "@" << s.mutualConnections[i] << (i + 1 < s.mutualConnections.size() ? ", " : "");
                }
                std::cout << "\n";
            } else {
                std::cout << "    " << Color::YELLOW << "Discovered via " << s.distance << "-hop extended network\n" << Color::RESET;
            }
        }
    }
}

int main() {
    printBanner();

    pixora::Graph graph;
    loadSampleData(graph);

    int choice = -1;
    while (choice != 0) {
        std::cout << Color::BOLD << "\n============= Pixora Graph Operations =============\n" << Color::RESET;
        std::cout << " 1. Follow a User (" << Color::GREEN << "follow" << Color::RESET << ")\n";
        std::cout << " 2. Unfollow a User (" << Color::RED << "unfollow" << Color::RESET << ")\n";
        std::cout << " 3. View Followers of a User (" << Color::CYAN << "followers" << Color::RESET << ")\n";
        std::cout << " 4. View Following of a User (" << Color::CYAN << "following" << Color::RESET << ")\n";
        std::cout << " 5. Mutual Explorer (" << Color::MAGENTA << "mutual" << Color::RESET << ")\n";
        std::cout << " 6. BFS Suggestions (" << Color::YELLOW << "BFS recommendations" << Color::RESET << ")\n";
        std::cout << " 7. Print Full Network Adjacency Graph\n";
        std::cout << " 8. Reset / Reload Default Sample Network\n";
        std::cout << " 0. Exit\n";
        std::cout << "===================================================\n";
        std::cout << "Enter your choice [0-8]: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << Color::RED << "Invalid input. Please enter a number between 0 and 8.\n" << Color::RESET;
            continue;
        }

        switch (choice) {
            case 1:
                handleFollow(graph);
                break;
            case 2:
                handleUnfollow(graph);
                break;
            case 3:
                handleFollowers(graph);
                break;
            case 4:
                handleFollowing(graph);
                break;
            case 5:
                handleMutual(graph);
                break;
            case 6:
                handleBFSSuggestions(graph);
                break;
            case 7:
                graph.printGraph();
                break;
            case 8:
                loadSampleData(graph);
                break;
            case 0:
                std::cout << Color::GREEN << "\nThank you for using Pixora Graph Engine! Happy pinning!\n\n" << Color::RESET;
                break;
            default:
                std::cout << Color::RED << "Unknown choice. Please select from 0 to 8.\n" << Color::RESET;
                break;
        }
    }

    return 0;
}
