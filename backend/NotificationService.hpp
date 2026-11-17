#ifndef PIXORA_NOTIFICATION_SERVICE_HPP
#define PIXORA_NOTIFICATION_SERVICE_HPP

#include <string>
#include <vector>

namespace Pixora {

struct NotificationItem {
    std::string id;
    std::string message;
    std::string type; // "like", "save", "follow", "comment", "create"
    std::string avatar;
    std::string timestamp;

    std::string toJson() const;
};

class NotificationService {
private:
    std::vector<NotificationItem> notifications;

public:
    NotificationService();

    void addNotification(const std::string& message, const std::string& type, const std::string& avatar = "");
    const std::vector<NotificationItem>& getNotifications() const { return notifications; }
    std::string toJson() const;
    void seedInitialNotifications();
};

} // namespace Pixora

#endif // PIXORA_NOTIFICATION_SERVICE_HPP
