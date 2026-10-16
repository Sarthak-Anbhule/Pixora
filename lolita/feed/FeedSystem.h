// FeedSystem.h
// Pixora - Feed System class declaration
// Author: Lolita Gudme
// Implements: Per-user Queue, Fan-out on Post, Paging with K Pins

#ifndef FEEDSYSTEM_H
#define FEEDSYSTEM_H

#include <string>
#include <vector>
#include "MyQueue.h"
#include "MyHashMap.h"
using namespace std;

class FeedSystem {
private:
    // user_id -> MyQueue* (each user's feed)
    MyHashMap<MyQueue*>* user_feeds;

    // user_id -> vector<string>* (list of follower ids)
    MyHashMap<vector<string>*>* followers_map;

    int total_pins_posted;

public:
    FeedSystem();
    ~FeedSystem();

    // ---- User management ----
    bool create_user(string user_id);
    bool user_exists(string user_id);

    // ---- Follow graph ----
    bool follow(string follower_id, string followee_id);
    bool unfollow(string follower_id, string followee_id);

    // ---- Fan-out on post ----
    bool post_pin(string user_id, Pin p);

    // ---- Paging with K pins ----
    vector<Pin> get_feed_paged(string user_id, int page_number, int k_pins);

    // ---- Stats ----
    int get_feed_size(string user_id);
    int get_total_pins_posted();
};

#endif
