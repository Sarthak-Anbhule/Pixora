#ifndef PIXORA_PROFILE_HPP
#define PIXORA_PROFILE_HPP

#include <string>
#include <vector>

namespace Pixora {

class Profile {
private:
    std::string name;
    std::string handle;
    std::string title;
    std::string bio;
    std::string avatar;
    std::string coverImage;
    std::string website;
    std::string location;
    int followersCount{1840};
    int followingCount{392};
    int savesCount{148};

public:
    Profile();

    std::string getName() const { return name; }
    std::string getHandle() const { return handle; }
    std::string getTitle() const { return title; }
    std::string getBio() const { return bio; }
    std::string getAvatar() const { return avatar; }
    std::string getCoverImage() const { return coverImage; }
    std::string getWebsite() const { return website; }
    std::string getLocation() const { return location; }
    int getFollowersCount() const { return followersCount; }
    int getFollowingCount() const { return followingCount; }
    int getSavesCount() const { return savesCount; }

    void setName(const std::string& val) { name = val; }
    void setHandle(const std::string& val) { handle = val; }
    void setTitle(const std::string& val) { title = val; }
    void setBio(const std::string& val) { bio = val; }
    void setAvatar(const std::string& val) { avatar = val; }
    void setCoverImage(const std::string& val) { coverImage = val; }
    void setWebsite(const std::string& val) { website = val; }
    void setLocation(const std::string& val) { location = val; }
    void setFollowersCount(int val) { followersCount = val; }
    void setFollowingCount(int val) { followingCount = val; }
    void setSavesCount(int val) { savesCount = val; }

    std::string toJson() const;
    static Profile fromJson(const std::string& json);
};

} // namespace Pixora

#endif // PIXORA_PROFILE_HPP
