#ifndef PIXORA_PIN_CREATOR_HPP
#define PIXORA_PIN_CREATOR_HPP

#include <string>
#include <vector>
#include "Pin.hpp"
#include "FeedManager.hpp"
#include "Profile.hpp"

namespace Pixora {

class PinCreator {
private:
    FeedManager& feedManager;
    Profile& profile;

public:
    PinCreator(FeedManager& feed, Profile& prof);

    bool createPin(const std::string& title, const std::string& description,
                   const std::string& imageUrl, const std::string& category,
                   const std::string& board, const std::string& tagsCsv,
                   const std::string& sourceUrl, Pin& outPin, std::string& outError);

    bool createPinFromJson(const std::string& json, Pin& outPin, std::string& outError);
};

} // namespace Pixora

#endif // PIXORA_PIN_CREATOR_HPP
