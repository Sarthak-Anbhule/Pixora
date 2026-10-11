// ============================================================
//  main.cpp
//  Demo driver for Pinterest Chat & Notification module
//  Author: Tejaswini
// ============================================================
#include "NotificationQueue.h"
#include "ChatList.h"
#include <iostream>
#include <limits>
using namespace std;

int readNumber() {
    int n;
    while (!(cin >> n)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Please enter a number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return n;
}

void showMenu(int unread, int pending) {
    cout << "\n==============================================\n";
    cout << "   PINTEREST CHAT & NOTIFICATION SYSTEM\n";
    cout << "   Unread messages: " << unread
         << "  |  Pending notifications: " << pending << "\n";
    cout << "==============================================\n";
    cout << " 1. Receive a chat message\n";
    cout << " 2. Send a chat message\n";
    cout << " 3. Add an activity notification\n";
    cout << " 4. Process next notification\n";
    cout << " 5. Process all notifications\n";
    cout << " 6. View pending notifications\n";
    cout << " 7. Open chat (navigate next / previous)\n";
    cout << " 8. View full chat (oldest -> newest)\n";
    cout << " 9. View full chat (newest -> oldest)\n";
    cout << "10. Show unread counter\n";
    cout << "11. Mark all messages as read\n";
    cout << " 0. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    NotificationQueue notifications;
    ChatList chat;
    int choice;

    do {
        showMenu(chat.getUnreadCount(), notifications.size());
        choice = readNumber();
        cout << "\n";

        if (choice == 1) {
            string sender, text;
            cout << "  Sender name: "; getline(cin, sender);
            cout << "  Message: ";     getline(cin, text);
            chat.addMessage(sender, text, true);
            notifications.enqueue("Message", "New message from " + sender);
            cout << "  Message received. Unread counter increased.\n";

        } else if (choice == 2) {
            string text;
            cout << "  Your message: "; getline(cin, text);
            chat.addMessage("Me", text, false);
            cout << "  Message sent.\n";

        } else if (choice == 3) {
            string type, text;
            cout << "  Type (e.g. Pin Saved, Follow, Comment): "; getline(cin, type);
            cout << "  Details: ";                              getline(cin, text);
            notifications.enqueue(type, text);
            cout << "  Notification added to the queue.\n";

        } else if (choice == 4)  { notifications.processNext(); }
        else if (choice == 5)    { notifications.processAll();  }
        else if (choice == 6)    { notifications.display();     }
        else if (choice == 7)    { chat.openChat();             }
        else if (choice == 8)    { chat.displayForward();       }
        else if (choice == 9)    { chat.displayBackward();      }
        else if (choice == 10) {
            cout << "  You have " << chat.getUnreadCount()
                 << " unread message(s) out of " << chat.getTotal() << " total.\n";
        }
        else if (choice == 11)   { chat.markAllRead();          }
        else if (choice == 0)    { cout << "  Goodbye!\n";      }
        else                     { cout << "  Invalid option.\n"; }

    } while (choice != 0);

    return 0;
}