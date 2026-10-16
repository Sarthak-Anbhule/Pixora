// FeedSystem.cpp
// Pixora - Feed System implementation
// Author: Lolita Gudme

#include "FeedSystem.h"
#include <iostream>
using namespace std;

FeedSystem::FeedSystem() {
    user_feeds = new MyHashMap<MyQueue*>();
    followers_map = new MyHashMap<vector<string>*>();
    total_pins_posted = 0;
}

// Destructor intentionally minimal for demo.
// Full cleanup would iterate each map and delete stored pointers.
FeedSystem::~FeedSystem() {
    // no-op for demo
}

bool FeedSystem::create_user(string user_id) {
    if (user_feeds->contains(user_id)) return false;
    user_feeds->put(user_id, new MyQueue());
    followers_map->put(user_id, new vector<string>());
    return true;
}

bool FeedSystem::user_exists(string user_id) {
    return user_feeds->contains(user_id);
}

bool FeedSystem::follow(string follower_id, string followee_id) {
    if (!user_exists(follower_id) || !user_exists(followee_id)) return false;

    vector<string>* followers = *(followers_map->get(followee_id));
    for (size_t i = 0; i < followers->size(); i++) {
        if ((*followers)[i] == follower_id) return true;
    }
    followers->push_back(follower_id);
    return true;
}

bool FeedSystem::unfollow(string follower_id, string followee_id) {
    if (!user_exists(follower_id) || !user_exists(followee_id)) return false;

    vector<string>* followers = *(followers_map->get(followee_id));
    for (size_t i = 0; i < followers->size(); i++) {
        if ((*followers)[i] == follower_id) {
            followers->erase(followers->begin() + i);
            return true;
        }
    }
    return false;
}

bool FeedSystem::post_pin(string user_id, Pin p) {
    if (!user_exists(user_id)) return false;

    // 1. Author sees their own pin
    MyQueue* author_feed = *(user_feeds->get(user_id));
    author_feed->enqueue(p);

    // 2. Fan-out to every follower
    vector<string>* followers = *(followers_map->get(user_id));
    for (size_t i = 0; i < followers->size(); i++) {
        string follower_id = (*followers)[i];
        MyQueue* follower_feed = *(user_feeds->get(follower_id));
        if (follower_feed != 0) {
            follower_feed->enqueue(p);
        }
    }

    total_pins_posted++;
    return true;
}

vector<Pin> FeedSystem::get_feed_paged(string user_id, int page_number, int k_pins) {
    vector<Pin> result;
    if (!user_exists(user_id)) {
        Pin err;
        err.pin_id = -1;
        err.title = "USER_NOT_FOUND";
        result.push_back(err);
        return result;
    }
    if (page_number < 1 || k_pins < 1) return result;

    MyQueue* feed = *(user_feeds->get(user_id));
    int total = feed->size();

    int start = (page_number - 1) * k_pins;
    int end = start + k_pins;

    if (start >= total) return result;

    Pin* all = feed->to_array();
    for (int i = start; i < end && i < total; i++) {
        result.push_back(all[i]);
    }
    delete[] all;
    return result;
}

int FeedSystem::get_feed_size(string user_id) {
    if (!user_exists(user_id)) return 0;
    MyQueue* feed = *(user_feeds->get(user_id));
    return feed->size();
}

int FeedSystem::get_total_pins_posted() {
    return total_pins_posted;
}
