//
// Created by Zebin Guo on 12/10/24.
//
#include "subStringReplacement.hpp"

String subStringReplacement::subStringReplacement_1_3(const String& originalStr, const char *originalPattern, const char *replacedPattern) {
    size_t index = 0;
    String result{};
    while (index < originalStr.size()) {
        int found = originalStr.find(originalPattern, index);
        std::cout << "found: " << found << std::endl;
        if (found == String::npos) {
            result += originalStr.substr(index);
            return result;
        }
        result += originalStr.substr(index, found);
        result += replacedPattern;
        index = found + strlen(originalPattern);
    }
    return result;
}
