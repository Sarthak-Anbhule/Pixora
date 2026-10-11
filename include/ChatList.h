// ============================================================
//  ChatList.h
//  Doubly Linked List for chat messages with unread tracking
//  Author: Tejaswini
// ============================================================
#ifndef CHAT_LIST_H
#define CHAT_LIST_H

#include <string>
using namespace std;

// A single chat message node
struct Message {
    string sender;
    string text;
    bool   incoming;   // true = received, false = sent by me
    bool   isRead;     // has this message been viewed?
    Message* prev;     // older message
    Message* next;     // newer message
};

class ChatList {
private:
    Message* head;         // oldest message
    Message* tail;         // newest message
    Message* current;      // message being viewed during navigation
    int total;             // total number of messages
    int unreadCount;       // number of unread incoming messages

    void showMessage(Message* m) const;
    void markAsRead(Message* m);

public:
    ChatList();
    ~ChatList();

    int getUnreadCount() const;
    int getTotal()       const;

    void addMessage(const string& sender, const string& text, bool incoming);
    void displayForward()  const;
    void displayBackward() const;
    void openChat();
    void markAllRead();
};

#endif // CHAT_LIST_H