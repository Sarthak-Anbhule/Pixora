#include "FeedManager.hpp"
#include "Utils.hpp"
#include <sstream>
#include <algorithm>

namespace Pixora {

FeedManager::FeedManager() {}

void FeedManager::addPin(const Pin& pin, bool prepend) {
    if (prepend) {
        pins.insert(pins.begin(), pin);
    } else {
        pins.push_back(pin);
    }
}

bool FeedManager::removePin(const std::string& pinId) {
    auto it = std::remove_if(pins.begin(), pins.end(),
        [&pinId](const Pin& p) { return p.getId() == pinId; });
    if (it != pins.end()) {
        pins.erase(it, pins.end());
        return true;
    }
    return false;
}

Pin* FeedManager::findPinById(const std::string& pinId) {
    for (auto& p : pins) {
        if (p.getId() == pinId) return &p;
    }
    return nullptr;
}

const Pin* FeedManager::findPinById(const std::string& pinId) const {
    for (const auto& p : pins) {
        if (p.getId() == pinId) return &p;
    }
    return nullptr;
}

std::vector<Pin> FeedManager::getSavedPins() const {
    std::vector<Pin> saved;
    for (const auto& p : pins) {
        if (p.getIsSaved()) saved.push_back(p);
    }
    return saved;
}

std::vector<Pin> FeedManager::getPinsByBoard(const std::string& boardTitle) const {
    std::vector<Pin> result;
    for (const auto& p : pins) {
        if (p.getIsSaved() && Utils::toLowerCase(p.getBoard()) == Utils::toLowerCase(boardTitle)) {
            result.push_back(p);
        }
    }
    return result;
}

std::vector<Pin> FeedManager::getPinsByCategory(const std::string& category) const {
    if (category == "all" || category.empty()) return pins;
    std::vector<Pin> result;
    for (const auto& p : pins) {
        if (Utils::toLowerCase(p.getCategory()) == Utils::toLowerCase(category)) {
            result.push_back(p);
        }
    }
    return result;
}

std::string FeedManager::pinsToJson(const std::vector<Pin>& list) const {
    std::ostringstream ss;
    ss << "[";
    for (size_t i = 0; i < list.size(); ++i) {
        ss << list[i].toJson();
        if (i + 1 < list.size()) ss << ",";
    }
    ss << "]";
    return ss.str();
}

std::string FeedManager::allPinsToJson() const {
    return pinsToJson(pins);
}

} // namespace Pixora
