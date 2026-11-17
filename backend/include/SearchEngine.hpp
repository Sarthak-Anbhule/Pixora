#ifndef PIXORA_SEARCH_ENGINE_HPP
#define PIXORA_SEARCH_ENGINE_HPP

#include <string>
#include <vector>
#include "Pin.hpp"

namespace Pixora {

class SearchEngine {
public:
    static std::vector<Pin> filterByCategory(const std::vector<Pin>& pins, const std::string& category);
    static std::vector<Pin> search(const std::vector<Pin>& pins, const std::string& query);
    static std::vector<Pin> searchCombined(const std::vector<Pin>& pins, const std::string& category, const std::string& query);
    static int calculateRelevanceScore(const Pin& pin, const std::string& query);
};

} // namespace Pixora

#endif // PIXORA_SEARCH_ENGINE_HPP
