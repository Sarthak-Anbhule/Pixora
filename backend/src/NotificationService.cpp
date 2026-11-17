#include "NotificationService.hpp"
#include "Utils.hpp"
#include <sstream>

namespace Pixora {

std::string NotificationItem::toJson() const {
    std::ostringstream ss;
    ss << "{"
       << "\"id\":\"" << Utils::escapeJson(id) << "\","
       << "\"message\":\"" << Utils::escapeJson(message) << "\","
       << "\"type\":\"" << Utils::escapeJson(type) << "\","
       << "\"avatar\":\"" << Utils::escapeJson(avatar) << "\","
       << "\"timestamp\":\"" << Utils::escapeJson(timestamp) << "\""
       << "}";
    return ss.str();
}

NotificationService::NotificationService() {
    seedInitialNotifications();
}

void NotificationService::addNotification(const std::string& message, const std::string& type, const std::string& avatar) {
    NotificationItem item;
    item.id = Utils::generateId("notif");
    item.message = message;
    item.type = type;
    item.avatar = avatar.empty() ? "https://images.unsplash.com/photo-1507003211169-0a1dd7228f2d?auto=format&fit=crop&w=100&q=80" : avatar;
    item.timestamp = "Just now";

    notifications.insert(notifications.begin(), item);
    if (notifications.size() > 50) {
        notifications.pop_back();
    }
}

std::string NotificationService::toJson() const {
    std::ostringstream ss;
    ss << "[";
    for (size_t i = 0; i < notifications.size(); ++i) {
        ss << notifications[i].toJson();
        if (i + 1 < notifications.size()) ss << ",";
    }
    ss << "]";
    return ss.str();
}

void NotificationService::seedInitialNotifications() {
    notifications.clear();
    notifications.push_back({
        "notif-1",
        "Kasper Lindqvist saved your pin Concrete Monolith Residence.",
        "save",
        "https://images.unsplash.com/photo-1507003211169-0a1dd7228f2d?auto=format&fit=crop&w=100&q=80",
        "2 hours ago"
    });
    notifications.push_back({
        "notif-2",
        "Oliver Thorne started following your inspiration boards.",
        "follow",
        "https://images.unsplash.com/photo-1522075469751-3a6694fb2f61?auto=format&fit=crop&w=100&q=80",
        "5 hours ago"
    });
    notifications.push_back({
        "notif-3",
        "Your collection Dream Architecture reached 1.4k saves this week.",
        "trending",
        "https://images.unsplash.com/photo-1600585154340-be6161a56a0c?auto=format&fit=crop&w=100&q=80",
        "Yesterday"
    });
}

} // namespace Pixora
