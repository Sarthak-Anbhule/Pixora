// MyQueue.h
// Pixora - Custom Queue (FIFO) implemented from scratch
// Author: Lolita Gudme
// No STL queue used.

#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <string>
using namespace std;

// A Pin is what gets stored in the feed.
struct Pin {
    int pin_id;
    string title;
};

// Node for linked-list based queue
struct QueueNode {
    Pin data;
    QueueNode* next;
    QueueNode(Pin p) : data(p), next(0) {}
};

class MyQueue {
private:
    QueueNode* front;
    QueueNode* rear;
    int count;

public:
    MyQueue() {
        front = 0;
        rear = 0;
        count = 0;
    }

    ~MyQueue() {
        while (!is_empty()) {
            dequeue();
        }
    }

    // Add to BACK of queue
    void enqueue(Pin p) {
        QueueNode* newNode = new QueueNode(p);
        if (rear == 0) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }

    // Remove from FRONT of queue
    Pin dequeue() {
        if (is_empty()) {
            Pin empty;
            empty.pin_id = -1;
            empty.title = "";
            return empty;
        }
        QueueNode* temp = front;
        Pin data = temp->data;
        front = front->next;
        if (front == 0) {
            rear = 0;
        }
        delete temp;
        count--;
        return data;
    }

    bool is_empty() {
        return front == 0;
    }

    int size() {
        return count;
    }

    // Copy queue contents into a plain array for paging
    // Caller must delete[] the returned array.
    Pin* to_array() {
        Pin* arr = new Pin[count];
        QueueNode* cur = front;
        int i = 0;
        while (cur != 0) {
            arr[i] = cur->data;
            i++;
            cur = cur->next;
        }
        return arr;
    }
};

#endif
