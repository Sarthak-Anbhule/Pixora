#ifndef PIXORA_FEED_MANAGER_HPP
#define PIXORA_FEED_MANAGER_HPP

#include <vector>
#include <memory>
#include "Pin.hpp"

namespace Pixora {

class FeedManager {
private:
    std::vector<Pin> pins;

public:
    FeedManager();

    void addPin(const Pin& pin, bool prepend = true);
    bool removePin(const std::string& pinId);
    Pin* findPinById(const std::string& pinId);
    const Pin* findPinById(const std::string& pinId) const;

    const std::vector<Pin>& getAllPins() const { return pins; }
    std::vector<Pin>& getAllPins() { return pins; }
    void setPins(const std::vector<Pin>& newPins) { pins = newPins; }

    std::vector<Pin> getSavedPins() const;
    std::vector<Pin> getPinsByBoard(const std::string& boardTitle) const;
    std::vector<Pin> getPinsByCategory(const std::string& category) const;

    std::string pinsToJson(const std::vector<Pin>& list) const;
    std::string allPinsToJson() const;
    size_t getCount() const { return pins.size(); }
};

} // namespace Pixora

#endif // PIXORA_FEED_MANAGER_HPP
