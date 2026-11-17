#ifndef PIXORA_BOARD_HPP
#define PIXORA_BOARD_HPP

#include <string>
#include <vector>

namespace Pixora {

class Board {
private:
    std::string id;
    std::string title;
    std::string description;
    std::string coverImage;
    int pinCount{0};
    bool isPrivate{false};
    std::string createdAt;

public:
    Board();
    Board(const std::string& id, const std::string& title, const std::string& description,
          const std::string& coverImage, int pinCount = 0, bool isPrivate = false);

    std::string getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getDescription() const { return description; }
    std::string getCoverImage() const { return coverImage; }
    int getPinCount() const { return pinCount; }
    bool getIsPrivate() const { return isPrivate; }
    std::string getCreatedAt() const { return createdAt; }

    void setId(const std::string& val) { id = val; }
    void setTitle(const std::string& val) { title = val; }
    void setDescription(const std::string& val) { description = val; }
    void setCoverImage(const std::string& val) { coverImage = val; }
    void setPinCount(int val) { pinCount = val; }
    void incrementPinCount() { pinCount++; }
    void decrementPinCount() { if (pinCount > 0) pinCount--; }
    void setIsPrivate(bool val) { isPrivate = val; }

    std::string toJson() const;
    static Board fromJson(const std::string& json);
};

} // namespace Pixora

#endif // PIXORA_BOARD_HPP
