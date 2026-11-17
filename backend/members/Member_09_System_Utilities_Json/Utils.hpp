/**
 * PIXORA C++ Engine - Member 09 Contribution
 * Subsystem: System Utilities & JSON Formatting
 */

#ifndef PIXORA_UTILS_HPP
#define PIXORA_UTILS_HPP

#include <string>
#include <vector>

namespace Pixora {

class Utils {
public:
    static std::string trim(const std::string& str);
    static std::string toLowerCase(const std::string& str);
    static std::vector<std::string> split(const std::string& s, char delimiter);
    static std::string escapeJson(const std::string& s);
    static std::string urlDecode(const std::string& src);
    static std::string getCurrentDate();
    static std::string generateId(const std::string& prefix = "id");
    static bool containsIgnoreCase(const std::string& source, const std::string& target);
};

} // namespace Pixora

#endif // PIXORA_UTILS_HPP
