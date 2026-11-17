#include "PinCreator.hpp"
#include "Utils.hpp"
#include "JsonHelper.hpp"

namespace Pixora {

PinCreator::PinCreator(FeedManager& feed, Profile& prof)
    : feedManager(feed), profile(prof) {}

bool PinCreator::createPin(const std::string& title, const std::string& description,
                           const std::string& imageUrl, const std::string& category,
                           const std::string& board, const std::string& tagsCsv,
                           const std::string& sourceUrl, Pin& outPin, std::string& outError) {
    std::string cleanTitle = Utils::trim(title);
    if (cleanTitle.empty()) {
        outError = "Pin title cannot be empty.";
        return false;
    }

    std::string cleanImg = Utils::trim(imageUrl);
    if (cleanImg.empty()) {
        outError = "Image URL or data must be provided.";
        return false;
    }

    Author author;
    author.name = profile.getName();
    author.handle = profile.getHandle();
    author.avatar = profile.getAvatar();
    author.verified = true;
    author.followers = profile.getFollowersCount();

    std::string pinId = Utils::generateId("pin");
    Pin pin(pinId, cleanTitle, Utils::trim(description), cleanImg,
            category.empty() ? "art-design" : category,
            board.empty() ? "Creative Inspiration" : board,
            author);

    pin.setSourceUrl(Utils::trim(sourceUrl));
    pin.setIsSaved(true);
    pin.setSaves(1);

    // Parse tags
    std::vector<std::string> rawTags = Utils::split(tagsCsv, ',');
    for (auto& t : rawTags) {
        if (!t.empty() && t[0] == '#') t = t.substr(1);
        if (!t.empty()) pin.addTag(t);
    }

    feedManager.addPin(pin, true); // prepend to top of feed
    outPin = pin;
    return true;
}

bool PinCreator::createPinFromJson(const std::string& json, Pin& outPin, std::string& outError) {
    std::string title = JsonHelper::getString(json, "title");
    std::string desc = JsonHelper::getString(json, "description");
    std::string img = JsonHelper::getString(json, "imageUrl");
    std::string cat = JsonHelper::getString(json, "category");
    std::string board = JsonHelper::getString(json, "board");
    std::string src = JsonHelper::getString(json, "sourceUrl");

    std::vector<std::string> tags = JsonHelper::getArrayOfStrings(json, "tags");
    std::string tagsCsv = "";
    for (size_t i = 0; i < tags.size(); ++i) {
        tagsCsv += tags[i];
        if (i + 1 < tags.size()) tagsCsv += ",";
    }

    return createPin(title, desc, img, cat, board, tagsCsv, src, outPin, outError);
}

} // namespace Pixora
