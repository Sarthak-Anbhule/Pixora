// ============================================================
//  ChatList.cpp
//  Implementation of the doubly linked chat list
//  Author: Tejaswini
// ============================================================
#include "ChatList.h"
#include <iostream>
#include <limits>
#include <cctype>
using namespace std;

ChatList::ChatList()
    : head(NULL), tail(NULL), current(NULL), total(0), unreadCount(0) {}

ChatList::~ChatList() {
    while (head != NULL) {
        Message* temp = head;
        head = head->next;
        delete temp;
    }
}

int ChatList::getUnreadCount() const { return unreadCount; }
int ChatList::getTotal()       const { return total; }

void ChatList::showMessage(Message* m) const {
    cout << "  " << (m->incoming ? "<- " : "-> ")
         << m->sender << ": " << m->text;
    if (m->incoming && !m->isRead) {
        cout << "   (NEW)";
    }
    cout << "\n";
}

void ChatList::markAsRead(Message* m) {
    if (m->incoming && !m->isRead) {
        m->isRead = true;
        unreadCount--;
    }
}

void ChatList::addMessage(const string& sender, const string& text, bool incoming) {
    Message* m = new Message;
    m->sender   = sender;
    m->text     = text;
    m->incoming = incoming;
    m->isRead   = !incoming;   // my own messages count as read
    m->prev     = tail;
    m->next     = NULL;

    if (head == NULL) {
        head = tail = m;
    } else {
        tail->next = m;
        tail = m;
    }
    total++;

    if (incoming) {
        unreadCount++;
    }
}

void ChatList::displayForward() const {
    if (head == NULL) {
        cout << "  No messages yet.\n";
        return;
    }
    cout << "  --- Chat history (oldest -> newest) ---\n";
    for (Message* cur = head; cur != NULL; cur = cur->next) {
        showMessage(cur);
    }
}

void ChatList::displayBackward() const {
    if (tail == NULL) {
        cout << "  No messages yet.\n";
        return;
    }
    cout << "  --- Chat history (newest -> oldest) ---\n";
    for (Message* cur = tail; cur != NULL; cur = cur->prev) {
        showMessage(cur);
    }
}

void ChatList::openChat() {
    if (head == NULL) {
        cout << "  No messages yet.\n";
        return;
    }

    // Start at the first unread message, or the newest if all are read
    current = head;
    while (current != NULL && !(current->incoming && !current->isRead)) {
        current = current->next;
    }
    if (current == NULL) {
        current = tail;
    }

    char choice;
    do {
        markAsRead(current);
        cout << "\n  Currently viewing:\n";
        showMessage(current);
        cout << "  (Unread messages left: " << unreadCount << ")\n";
        cout << "  [N] Next (newer)  [P] Previous (older)  [Q] Quit chat: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        choice = toupper(choice);

        if (choice == 'N') {
            if (current->next != NULL) current = current->next;
            else cout << "  You are at the newest message.\n";
        } else if (choice == 'P') {
            if (current->prev != NULL) current = current->prev;
            else cout << "  You are at the oldest message.\n";
        } else if (choice != 'Q') {
            cout << "  Invalid choice. Try N, P, or Q.\n";
        }
    } while (choice != 'Q');
}

void ChatList::markAllRead() {
    for (Message* cur = head; cur != NULL; cur = cur->next) {
        markAsRead(cur);
    }
    cout << "  All messages marked as read.\n";
}