// ============================================================
//  NotificationQueue.cpp
//  Implementation of the FIFO notification queue
//  Author: Tejaswini
// ============================================================
#include "NotificationQueue.h"
#include <iostream>
using namespace std;

NotificationQueue::NotificationQueue()
    : front(NULL), rear(NULL), count(0) {}

NotificationQueue::~NotificationQueue() {
    while (!isEmpty()) {
        dequeue();
    }
}

bool NotificationQueue::isEmpty() const {
    return front == NULL;
}

int NotificationQueue::size() const {
    return count;
}

void NotificationQueue::enqueue(const string& type, const string& text) {
    Notification* n = new Notification;
    n->type = type;
    n->text = text;
    n->next = NULL;

    if (isEmpty()) {
        front = rear = n;
    } else {
        rear->next = n;
        rear = n;
    }
    count++;
}

bool NotificationQueue::dequeue() {
    if (isEmpty()) return false;

    Notification* temp = front;
    front = front->next;
    if (front == NULL) rear = NULL;
    delete temp;
    count--;
    return true;
}

void NotificationQueue::processNext() {
    if (isEmpty()) {
        cout << "  No notifications to process.\n";
        return;
    }
    cout << "  Processing -> [" << front->type << "] " << front->text << "\n";
    dequeue();
}

void NotificationQueue::processAll() {
    if (isEmpty()) {
        cout << "  No notifications to process.\n";
        return;
    }
    while (!isEmpty()) {
        processNext();
    }
}

void NotificationQueue::display() const {
    if (isEmpty()) {
        cout << "  Notification queue is empty.\n";
        return;
    }
    cout << "  Pending notifications (front -> rear):\n";
    Notification* cur = front;
    int i = 1;
    while (cur != NULL) {
        cout << "   " << i++ << ". [" << cur->type << "] " << cur->text << "\n";
        cur = cur->next;
    }
}