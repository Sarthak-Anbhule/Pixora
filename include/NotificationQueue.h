// ============================================================
//  NotificationQueue.h
//  FIFO Queue for Pinterest activity notifications
//  Author: Tejaswini
// ============================================================
#ifndef NOTIFICATION_QUEUE_H
#define NOTIFICATION_QUEUE_H

#include <string>
using namespace std;

// A single notification node in the queue
struct Notification {
    string type;          // e.g. "Message", "Pin Saved", "Follow", "Comment"
    string text;          // notification body
    Notification* next;   // pointer to next notification
};

class NotificationQueue {
private:
    Notification* front;  // oldest notification (next to be processed)
    Notification* rear;   // newest notification
    int count;            // number of pending notifications

public:
    NotificationQueue();
    ~NotificationQueue();

    bool isEmpty() const;
    int  size()    const;

    void enqueue(const string& type, const string& text);
    bool dequeue();
    void processNext();
    void processAll();
    void display() const;
};

#endif // NOTIFICATION_QUEUE_H