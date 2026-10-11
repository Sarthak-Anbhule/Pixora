#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <algorithm>
#include "Graph.h"

// Simple testing assertions and helpers
#define TEST_ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            std::cerr << "[\033[31mFAIL\033[0m] " << msg << " (" << __FILE__ << ":" << __LINE__ << ")\n"; \
            std::exit(1); \
        } \
    } while(0)

#define TEST_PASS(msg) \
    std::cout << "[\033[32mPASS\033[0m] " << msg << "\n"

void testUserManagement() {
    pixora::Graph g;
    TEST_ASSERT(g.addUser("alice"), "Should add user alice");
    TEST_ASSERT(!g.addUser("alice"), "Should reject duplicate user alice");
    TEST_ASSERT(!g.addUser(""), "Should reject empty username");
    TEST_ASSERT(g.addUser("bob"), "Should add user bob");
    TEST_ASSERT(g.hasUser("alice"), "alice should exist");
    TEST_ASSERT(g.hasUser("bob"), "bob should exist");
    TEST_ASSERT(!g.hasUser("charlie"), "charlie should not exist yet");
    TEST_ASSERT(g.getUserCount() == 2, "User count should be 2");

    auto users = g.getAllUsers();
    TEST_ASSERT(users.size() == 2 && users[0] == "alice" && users[1] == "bob", "getAllUsers should return sorted users");

    TEST_PASS("testUserManagement passed");
}

void testFollowAndUnfollow() {
    pixora::Graph g;
    TEST_ASSERT(g.follow("alice", "bob"), "alice should follow bob");
    TEST_ASSERT(!g.follow("alice", "bob"), "Duplicate follow should return false");
    TEST_ASSERT(!g.follow("alice", "alice"), "Self-follow should return false");
    TEST_ASSERT(g.isFollowing("alice", "bob"), "alice should be following bob");
    TEST_ASSERT(!g.isFollowing("bob", "alice"), "bob is not following alice");
    TEST_ASSERT(g.getTotalEdges() == 1, "Total edges should be 1");

    // Auto-registration test
    TEST_ASSERT(g.hasUser("alice") && g.hasUser("bob"), "Users should auto-register on follow");

    // Unfollow
    TEST_ASSERT(g.unfollow("alice", "bob"), "alice unfollow bob should succeed");
    TEST_ASSERT(!g.unfollow("alice", "bob"), "Repeat unfollow should return false");
    TEST_ASSERT(!g.isFollowing("alice", "bob"), "alice is no longer following bob");
    TEST_ASSERT(g.getTotalEdges() == 0, "Total edges should be 0");

    TEST_PASS("testFollowAndUnfollow passed");
}

void testFollowersAndFollowing() {
    pixora::Graph g;
    g.follow("alice", "bob");
    g.follow("alice", "charlie");
    g.follow("charlie", "bob");

    // Alice follows bob and charlie
    auto aliceFollowing = g.following("alice");
    TEST_ASSERT(aliceFollowing.size() == 2, "Alice following count 2");
    TEST_ASSERT(aliceFollowing[0] == "bob" && aliceFollowing[1] == "charlie", "Alice following list matches");

    // Bob has followers alice and charlie
    auto bobFollowers = g.followers("bob");
    TEST_ASSERT(bobFollowers.size() == 2, "Bob followers count 2");
    TEST_ASSERT(bobFollowers[0] == "alice" && bobFollowers[1] == "charlie", "Bob followers list matches");

    // Charlie follows bob, followed by alice
    TEST_ASSERT(g.getFollowingCount("charlie") == 1, "Charlie following count 1");
    TEST_ASSERT(g.getFollowersCount("charlie") == 1, "Charlie followers count 1");

    TEST_PASS("testFollowersAndFollowing passed");
}

void testMutual() {
    pixora::Graph g;
    // Alice follows: art, design, tech
    g.follow("alice", "art");
    g.follow("alice", "design");
    g.follow("alice", "tech");

    // Bob follows: design, tech, cooking
    g.follow("bob", "design");
    g.follow("bob", "tech");
    g.follow("bob", "cooking");

    // Mutual followings between Alice and Bob: design, tech
    auto common = g.mutual("alice", "bob");
    TEST_ASSERT(common.size() == 2, "Alice and Bob should have 2 mutual followings");
    TEST_ASSERT(common[0] == "design" && common[1] == "tech", "Mutual accounts are design and tech");

    // Bidirectional mutual follow test ("are mutuals")
    TEST_ASSERT(!g.isMutualFollow("alice", "bob"), "Alice and Bob do not follow each other yet");
    g.follow("alice", "bob");
    TEST_ASSERT(!g.isMutualFollow("alice", "bob"), "Alice follows Bob, but Bob does not follow Alice");
    g.follow("bob", "alice");
    TEST_ASSERT(g.isMutualFollow("alice", "bob"), "Now Alice and Bob follow each other bidirectionally");

    // Mutual followers test (who follows both Alice and Bob?)
    g.follow("charlie", "alice");
    g.follow("charlie", "bob");
    g.follow("david", "alice");

    auto mutualFollowers = g.getMutualFollowers("alice", "bob");
    TEST_ASSERT(mutualFollowers.size() == 1 && mutualFollowers[0] == "charlie", "Charlie follows both");

    TEST_PASS("testMutual passed");
}

void testBFSSuggestions() {
    pixora::Graph g;
    /*
     Scenario:
     Alice follows Bob and Charlie.
     Bob follows David and Emma.
     Charlie follows David and Fiona.
     David is followed by BOTH Bob and Charlie (2 mutual connections for Alice!).
     Emma is followed by Bob (1 mutual connection for Alice).
     Fiona is followed by Charlie (1 mutual connection for Alice).
     David also follows George (distance 3 from Alice).
    */
    g.follow("alice", "bob");
    g.follow("alice", "charlie");

    g.follow("bob", "david");
    g.follow("bob", "emma");

    g.follow("charlie", "david");
    g.follow("charlie", "fiona");

    g.follow("david", "george");

    // Top 5 BFS suggestions for Alice up to depth 3
    auto suggestions = g.bfsSuggestions("alice", 5, 3);

    TEST_ASSERT(!suggestions.empty(), "Suggestions should not be empty");

    // Alice should NEVER be suggested to herself, nor bob or charlie (already following)
    for (const auto& s : suggestions) {
        TEST_ASSERT(s.username != "alice", "Cannot suggest self");
        TEST_ASSERT(s.username != "bob" && s.username != "charlie", "Cannot suggest already followed creators");
    }

    // David must be ranked #1 because David has 2 mutual connections (bob and charlie)
    TEST_ASSERT(suggestions[0].username == "david", "David should be top suggestion with 2 mutual connections");
    TEST_ASSERT(suggestions[0].distance == 2, "David distance is 2");
    TEST_ASSERT(suggestions[0].mutualConnectionsCount == 2, "David mutual connection count is 2");
    TEST_ASSERT(suggestions[0].mutualConnections[0] == "bob" && suggestions[0].mutualConnections[1] == "charlie",
                "David mutual connectors are bob and charlie");

    // Distance 3 candidate: George
    bool foundGeorge = false;
    for (const auto& s : suggestions) {
        if (s.username == "george") {
            foundGeorge = true;
            TEST_ASSERT(s.distance == 3, "George should be at distance 3");
            TEST_ASSERT(s.mutualConnectionsCount == 0, "George has 0 direct mutual connections from Alice's 1st hop");
        }
    }
    TEST_ASSERT(foundGeorge, "George should be suggested at depth 3");

    // Limit check
    auto top2 = g.bfsSuggestions("alice", 2, 2);
    TEST_ASSERT(top2.size() == 2, "Limit to 2 suggestions should return exactly 2");

    // Edge case: User with no followings
    g.addUser("lonely_user");
    auto emptySuggestions = g.bfsSuggestions("lonely_user", 5, 2);
    TEST_ASSERT(emptySuggestions.empty(), "Lonely user should get empty suggestions");

    TEST_PASS("testBFSSuggestions passed");
}

int main() {
    std::cout << "\n========== Running Pixora Graph Unit Tests ==========\n\n";

    testUserManagement();
    testFollowAndUnfollow();
    testFollowersAndFollowing();
    testMutual();
    testBFSSuggestions();

    std::cout << "\n\033[32m[ALL TESTS PASSED SUCCESSFULLY!]\033[0m\n\n";
    return 0;
}
