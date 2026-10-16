// main.cpp
// Pixora - Feed Module Demo Runner
// Author: Lolita Gudme

#include <iostream>
#include <string>
#include "FeedSystem.h"
using namespace std;

void banner() {
    cout << "=======================================================\n";
    cout << "        PIXORA  ::  Feed System Module\n";
    cout << "        Author: Lolita Gudme\n";
    cout << "=======================================================\n";
}

void seed_demo_data(FeedSystem& app) {
    string users[5] = {"aurora", "blaze", "cyra", "draco", "ember"};
    for (int i = 0; i < 5; i++) {
        app.create_user(users[i]);
    }

    // Follow relationships
    app.follow("aurora", "blaze");
    app.follow("aurora", "cyra");
    app.follow("cyra", "aurora");
    app.follow("draco", "aurora");
    app.follow("ember", "blaze");
    app.follow("blaze", "aurora");
}

void show_feed(FeedSystem& app, string user, int page, int k) {
    cout << "\n--- " << user << "'s Feed | Page " << page << " | K = " << k << " ---\n";

    vector<Pin> pins = app.get_feed_paged(user, page, k);

    if (pins.size() == 1 && pins[0].pin_id == -1) {
        cout << "  User does not exist.\n";
        return;
    }
    if (pins.empty()) {
        cout << "  (No pins on this page)\n";
        return;
    }
    for (size_t i = 0; i < pins.size(); i++) {
        cout << "  " << (i + 1) << ". [" << pins[i].pin_id << "] " << pins[i].title << "\n";
    }
}

int main() {
    banner();
    FeedSystem app;
    seed_demo_data(app);

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Post a Pin (Fan-out)\n";
        cout << "2. View Feed (Paged)\n";
        cout << "3. Check Feed Size\n";
        cout << "4. List Demo Users\n";
        cout << "5. Exit\n";
        cout << "Choose: ";

        string choice;
        getline(cin, choice);

        if (choice == "1") {
            string user, title;
            cout << "Who is posting? ";
            getline(cin, user);
            cout << "Pin title: ";
            getline(cin, title);

            if (!app.user_exists(user)) {
                cout << "  Unknown user.\n";
                continue;
            }
            int pin_id = app.get_total_pins_posted() + 1;
            Pin p;
            p.pin_id = pin_id;
            p.title = title;
            app.post_pin(user, p);
            cout << "  Pin '" << title << "' posted by " << user << " (id=" << pin_id << ").\n";

        } else if (choice == "2") {
            string user;
            int page, k;
            cout << "Whose feed? ";
            getline(cin, user);
            cout << "Page number: ";
            cin >> page;
            cout << "K (pins per page): ";
            cin >> k;
            cin.ignore();
            show_feed(app, user, page, k);

        } else if (choice == "3") {
            string user;
            cout << "Whose feed size? ";
            getline(cin, user);
            cout << "  " << user << " has " << app.get_feed_size(user) << " pins in feed.\n";

        } else if (choice == "4") {
            cout << "\n  Demo users: aurora, blaze, cyra, draco, ember\n";
            cout << "  Follow graph:\n";
            cout << "    aurora  -> blaze, cyra\n";
            cout << "    cyra    -> aurora\n";
            cout << "    draco   -> aurora\n";
            cout << "    ember   -> blaze\n";
            cout << "    blaze   -> aurora\n";

        } else if (choice == "5") {
            cout << "Bye!\n";
            break;

        } else {
            cout << "  Invalid choice.\n";
        }
    }
    return 0;
}
