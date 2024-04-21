#pragma once
#include <vector>
namespace kckn {
    inline std::vector<std::string> split_string(const std::string& text, std::string delimiter) {
        std::vector<std::string> strings;
        size_t pos         = text.find(delimiter);
        size_t initial_pos = 0;
        while (pos != std::string::npos) {
            strings.push_back(text.substr(initial_pos, pos - initial_pos));
            initial_pos = pos + 1;

            pos = text.find(delimiter, initial_pos);
        }
        strings.push_back(text.substr(initial_pos, text.size() - initial_pos + 1));
        return strings;
    }
} // namespace kckn
