// MyHashMap.h
// Pixora - Custom Hash Map implemented from scratch using chaining
// Author: Lolita Gudme
// No STL unordered_map used.

#ifndef MYHASHMAP_H
#define MYHASHMAP_H

#include <string>
#include <vector>
using namespace std;

// Generic HashMap: Key = string (user_id), Value = template T
template <typename T>
struct HashNode {
    string key;
    T value;
    HashNode* next;
    HashNode(string k, T v) : key(k), value(v), next(0) {}
};

// Simple string hash function (djb2)
inline int hash_string(const string& s, int bucketCount) {
    unsigned long hash = 5381;
    for (size_t i = 0; i < s.size(); i++) {
        hash = ((hash << 5) + hash) + (unsigned char)s[i];
    }
    return hash % bucketCount;
}

template <typename T>
class MyHashMap {
private:
    static const int BUCKETS = 101;
    HashNode<T>* table[BUCKETS];
    int count;

public:
    MyHashMap() {
        for (int i = 0; i < BUCKETS; i++) table[i] = 0;
        count = 0;
    }

    ~MyHashMap() {
        for (int i = 0; i < BUCKETS; i++) {
            HashNode<T>* cur = table[i];
            while (cur != 0) {
                HashNode<T>* temp = cur;
                cur = cur->next;
                delete temp;
            }
        }
    }

    // Insert or update
    void put(string key, T value) {
        int idx = hash_string(key, BUCKETS);
        HashNode<T>* cur = table[idx];
        while (cur != 0) {
            if (cur->key == key) {
                cur->value = value;   // update existing
                return;
            }
            cur = cur->next;
        }
        // Not found -> insert at head
        HashNode<T>* newNode = new HashNode<T>(key, value);
        newNode->next = table[idx];
        table[idx] = newNode;
        count++;
    }

    // Returns pointer to value, or NULL if not found
    T* get(string key) {
        int idx = hash_string(key, BUCKETS);
        HashNode<T>* cur = table[idx];
        while (cur != 0) {
            if (cur->key == key) return &(cur->value);
            cur = cur->next;
        }
        return 0;
    }

    bool contains(string key) {
        return get(key) != 0;
    }

    int size() {
        return count;
    }
};

#endif
