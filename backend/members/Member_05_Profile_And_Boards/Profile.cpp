#include "Profile.hpp"
#include "Utils.hpp"
#include "JsonHelper.hpp"
#include <sstream>

namespace Pixora {

Profile::Profile()
    : name("Elena Vance"), handle("elenavance"),
      title("Architectural Designer & Visual Curator"),
      bio("Collecting light, brutalist shadows, timeless furniture, and serene travel moments. Based in Copenhagen 🇩🇰"),
      avatar("https://images.unsplash.com/photo-1534528741775-53994a69daeb?auto=format&fit=crop&w=400&q=80"),
      coverImage("https://images.unsplash.com/photo-1513694203232-719a280e022f?auto=format&fit=crop&w=1600&q=80"),
      website("https://elenavance.design"),
      location("Copenhagen, Denmark"),
      followersCount(1840), followingCount(392), savesCount(148) {}

std::string Profile::toJson() const {
    std::ostringstream ss;
    ss << "{"
       << "\"name\":\"" << Utils::escapeJson(name) << "\","
       << "\"handle\":\"" << Utils::escapeJson(handle) << "\","
       << "\"title\":\"" << Utils::escapeJson(title) << "\","
       << "\"bio\":\"" << Utils::escapeJson(bio) << "\","
       << "\"avatar\":\"" << Utils::escapeJson(avatar) << "\","
       << "\"coverImage\":\"" << Utils::escapeJson(coverImage) << "\","
       << "\"website\":\"" << Utils::escapeJson(website) << "\","
       << "\"location\":\"" << Utils::escapeJson(location) << "\","
       << "\"followersCount\":" << followersCount << ","
       << "\"followingCount\":" << followingCount << ","
       << "\"savesCount\":" << savesCount
       << "}";
    return ss.str();
}

Profile Profile::fromJson(const std::string& json) {
    Profile p;
    p.name = JsonHelper::getString(json, "name", p.name);
    p.handle = JsonHelper::getString(json, "handle", p.handle);
    p.title = JsonHelper::getString(json, "title", p.title);
    p.bio = JsonHelper::getString(json, "bio", p.bio);
    p.avatar = JsonHelper::getString(json, "avatar", p.avatar);
    p.coverImage = JsonHelper::getString(json, "coverImage", p.coverImage);
    p.website = JsonHelper::getString(json, "website", p.website);
    p.location = JsonHelper::getString(json, "location", p.location);
    p.followersCount = JsonHelper::getInt(json, "followersCount", p.followersCount);
    p.followingCount = JsonHelper::getInt(json, "followingCount", p.followingCount);
    p.savesCount = JsonHelper::getInt(json, "savesCount", p.savesCount);
    return p;
}

} // namespace Pixora
