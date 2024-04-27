#pragma once
#include <vector>
namespace kckn {
    inline std::string strip_string(std::string text, char c = ' ') {
        int leading_spaces  = 0;
        int trailing_spaces = 0;
        for (size_t i = 0; i < text.size(); i++) {
            if (text[i] == c) {
                leading_spaces++;
            } else {
                break;
            }
        }
        for (size_t i = text.size() - 1; i >= 0; i--) {
            if (text[i] == c) {
                trailing_spaces++;
            } else {
                break;
            }
        }
        return text.substr(leading_spaces, text.size() - leading_spaces - trailing_spaces);
    }
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
