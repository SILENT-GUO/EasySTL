//
// Created by Zebin Guo on 12/13/24.
//
#include "stringCompression.hpp"

String stringCompression::stringCompression_1_6(const String & originalString) {
    if (originalString.size() <= 1) return originalString;
    String result;
    char currentChar = originalString[0];
    int numberOfChars = 1;
    for (size_t index = 1; index < originalString.size(); index++) {
        if (currentChar == originalString[index]) {
            numberOfChars++;
        }
        else {
            result += String(1, currentChar) + String::to_String(numberOfChars);
            currentChar = originalString[index];
            numberOfChars = 1;
        }
    }
    result += String(1, currentChar) + String::to_String(numberOfChars);

    return (result.size() < originalString.size()) ? result : originalString;
}
