#include "SearchEngine.hpp"
#include "Utils.hpp"
#include <algorithm>

namespace Pixora {

std::vector<Pin> SearchEngine::filterByCategory(const std::vector<Pin>& pins, const std::string& category) {
    if (category.empty() || category == "all") return pins;
    std::string catLower = Utils::toLowerCase(category);
    std::vector<Pin> result;
    for (const auto& p : pins) {
        if (Utils::toLowerCase(p.getCategory()) == catLower) {
            result.push_back(p);
        }
    }
    return result;
}

int SearchEngine::calculateRelevanceScore(const Pin& pin, const std::string& query) {
    if (query.empty()) return 1;
    std::string q = Utils::toLowerCase(query);
    int score = 0;

    // Title match has highest weight
    if (Utils::containsIgnoreCase(pin.getTitle(), q)) score += 10;
    // Tags match
    for (const auto& t : pin.getTags()) {
        if (Utils::containsIgnoreCase(t, q)) score += 6;
    }
    // Board match
    if (Utils::containsIgnoreCase(pin.getBoard(), q)) score += 5;
    // Category match
    if (Utils::containsIgnoreCase(pin.getCategory(), q)) score += 4;
    // Author match
    if (Utils::containsIgnoreCase(pin.getAuthor().name, q) || Utils::containsIgnoreCase(pin.getAuthor().handle, q)) score += 3;
    // Description match
    if (Utils::containsIgnoreCase(pin.getDescription(), q)) score += 2;

    return score;
}

std::vector<Pin> SearchEngine::search(const std::vector<Pin>& pins, const std::string& query) {
    std::string q = Utils::trim(query);
    if (q.empty()) return pins;

    std::vector<std::pair<int, Pin>> scored;
    for (const auto& p : pins) {
        int score = calculateRelevanceScore(p, q);
        if (score > 0) {
            scored.push_back({score, p});
        }
    }

    // Sort by relevance score descending
    std::sort(scored.begin(), scored.end(),
              [](const std::pair<int, Pin>& a, const std::pair<int, Pin>& b) {
                  return a.first > b.first;
              });

    std::vector<Pin> result;
    for (const auto& item : scored) {
        result.push_back(item.second);
    }
    return result;
}

std::vector<Pin> SearchEngine::searchCombined(const std::vector<Pin>& pins, const std::string& category, const std::string& query) {
    std::vector<Pin> categoryFiltered = filterByCategory(pins, category);
    return search(categoryFiltered, query);
}

} // namespace Pixora
