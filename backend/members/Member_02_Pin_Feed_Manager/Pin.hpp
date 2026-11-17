/**
 * PIXORA C++ Engine - Member 02 Contribution
 * Subsystem: Pin Model & Feed Management Architecture
 */

#ifndef PIXORA_PIN_HPP
#define PIXORA_PIN_HPP

#include <string>
#include <vector>

namespace Pixora {

struct Author {
    std::string name;
    std::string handle;
    std::string avatar;
    bool verified{false};
    int followers{0};

    std::string toJson() const;
};

struct Comment {
    std::string id;
    std::string userName;
    std::string userAvatar;
    std::string text;
    std::string timestamp;

    std::string toJson() const;
};

class Pin {
private:
    std::string id;
    std::string title;
    std::string description;
    std::string imageUrl;
    std::string aspectRatio;
    int height{480};
    std::string category;
    std::string board;
    std::vector<std::string> tags;
    std::string sourceUrl;
    int likes{0};
    int saves{0};
    bool isLiked{false};
    bool isSaved{false};
    Author author;
    std::vector<Comment> comments;
    std::string createdAt;

public:
    Pin();
    Pin(const std::string& id, const std::string& title, const std::string& description,
        const std::string& imageUrl, const std::string& category, const std::string& board,
        const Author& author);

    // Getters
    std::string getId() const { return id; }
    std::string getTitle() const { return title; }
    std::string getDescription() const { return description; }
    std::string getImageUrl() const { return imageUrl; }
    std::string getAspectRatio() const { return aspectRatio; }
    int getHeight() const { return height; }
    std::string getCategory() const { return category; }
    std::string getBoard() const { return board; }
    const std::vector<std::string>& getTags() const { return tags; }
    std::string getSourceUrl() const { return sourceUrl; }
    int getLikes() const { return likes; }
    int getSaves() const { return saves; }
    bool getIsLiked() const { return isLiked; }
    bool getIsSaved() const { return isSaved; }
    const Author& getAuthor() const { return author; }
    const std::vector<Comment>& getComments() const { return comments; }
    std::string getCreatedAt() const { return createdAt; }

    // Setters & Mutators
    void setId(const std::string& val) { id = val; }
    void setTitle(const std::string& val) { title = val; }
    void setDescription(const std::string& val) { description = val; }
    void setImageUrl(const std::string& val) { imageUrl = val; }
    void setAspectRatio(const std::string& val) { aspectRatio = val; }
    void setHeight(int val) { height = val; }
    void setCategory(const std::string& val) { category = val; }
    void setBoard(const std::string& val) { board = val; }
    void setTags(const std::vector<std::string>& val) { tags = val; }
    void addTag(const std::string& tag) { tags.push_back(tag); }
    void setSourceUrl(const std::string& val) { sourceUrl = val; }
    void setLikes(int val) { likes = val; }
    void setSaves(int val) { saves = val; }
    void setIsLiked(bool val) { isLiked = val; }
    void setIsSaved(bool val) { isSaved = val; }
    void setAuthor(const Author& val) { author = val; }
    void setCreatedAt(const std::string& val) { createdAt = val; }

    // Interactions
    bool toggleLike();
    bool toggleSave(const std::string& targetBoard = "");
    void addComment(const Comment& comment);

    // Serialization
    std::string toJson() const;
    static Pin fromJson(const std::string& json);
};

} // namespace Pixora

#endif // PIXORA_PIN_HPP
