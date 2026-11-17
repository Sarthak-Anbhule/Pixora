#ifndef PIXORA_JSON_HELPER_HPP
#define PIXORA_JSON_HELPER_HPP

#include <string>
#include <vector>
#include <map>
#include "Utils.hpp"

namespace Pixora {

class JsonHelper {
public:
    static std::string getString(const std::string& json, const std::string& key, const std::string& fallback = "") {
        std::string pattern = "\"" + key + "\":";
        size_t pos = json.find(pattern);
        if (pos == std::string::npos) return fallback;

        pos += pattern.length();
        while (pos < json.length() && (json[pos] == ' ' || json[pos] == '\t' || json[pos] == '\n' || json[pos] == '\r')) {
            pos++;
        }

        if (pos < json.length() && json[pos] == '"') {
            pos++;
            size_t endPos = pos;
            while (endPos < json.length()) {
                if (json[endPos] == '"' && json[endPos - 1] != '\\') {
                    break;
                }
                endPos++;
            }
            if (endPos <= json.length()) {
                return json.substr(pos, endPos - pos);
            }
        }
        return fallback;
    }

    static int getInt(const std::string& json, const std::string& key, int fallback = 0) {
        std::string pattern = "\"" + key + "\":";
        size_t pos = json.find(pattern);
        if (pos == std::string::npos) return fallback;

        pos += pattern.length();
        while (pos < json.length() && (json[pos] == ' ' || json[pos] == '\t' || json[pos] == '\n' || json[pos] == '\r')) {
            pos++;
        }

        size_t endPos = pos;
        while (endPos < json.length() && (isdigit(json[endPos]) || json[endPos] == '-')) {
            endPos++;
        }

        if (endPos > pos) {
            try {
                return std::stoi(json.substr(pos, endPos - pos));
            } catch (...) {
                return fallback;
            }
        }
        return fallback;
    }

    static bool getBool(const std::string& json, const std::string& key, bool fallback = false) {
        std::string pattern = "\"" + key + "\":";
        size_t pos = json.find(pattern);
        if (pos == std::string::npos) return fallback;

        pos += pattern.length();
        while (pos < json.length() && (json[pos] == ' ' || json[pos] == '\t' || json[pos] == '\n' || json[pos] == '\r')) {
            pos++;
        }

        if (json.substr(pos, 4) == "true") return true;
        if (json.substr(pos, 5) == "false") return false;
        return fallback;
    }

    static std::vector<std::string> getArrayOfStrings(const std::string& json, const std::string& key) {
        std::vector<std::string> result;
        std::string pattern = "\"" + key + "\":";
        size_t pos = json.find(pattern);
        if (pos == std::string::npos) return result;

        size_t start = json.find('[', pos);
        size_t end = json.find(']', start);
        if (start == std::string::npos || end == std::string::npos) return result;

        std::string sub = json.substr(start + 1, end - start - 1);
        size_t i = 0;
        while (i < sub.length()) {
            if (sub[i] == '"') {
                size_t j = i + 1;
                while (j < sub.length() && !(sub[j] == '"' && sub[j-1] != '\\')) {
                    j++;
                }
                result.push_back(sub.substr(i + 1, j - i - 1));
                i = j + 1;
            } else {
                i++;
            }
        }
        return result;
    }
};

} // namespace Pixora

#endif // PIXORA_JSON_HELPER_HPP
