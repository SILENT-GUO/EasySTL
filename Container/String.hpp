//
// Created by Zebin Guo on 12/10/24.
//

#ifndef STRING_HPP
#define STRING_HPP
#include <cstring>
#include "Vector.hpp"
// We define the string to be the child of Vector class.

class String: public Vector<char> {
private:
    static const size_t HASH_BASE_B = 16;
    static const size_t HASH_MODULO_P = 31;
public:
    static const int npos = -1;

    String() = default;
    explicit String(const char* cstr) {
        const size_t len = strlen(cstr);
        this->reserve(len+1);
        // Warning!!! This operation is not recommended! If the resize operation is forgotten, the size variable is wrong!
        memcpy(this->data(), cstr, len+1);
        this->resize(len);
    }
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        for (size_t i = 0; i < str.size(); i++) {
            os << str[i];
        }
        return os;
    }
    [[nodiscard]] String substr(size_t start, size_t end = String::npos) const {
        if (start >= this->size()) {
            throw std::out_of_range("String::substr start position out of range!");
        }
        if (end == String::npos || end > this->size()) {
            // in this case we take all chars from and after
            end = this->size();
        }

        const size_t len = end - start;
        String result;
        result.reserve(len);
        memcpy(result.data(), this->data() + start, len);
        std::cout << this->data() << std::endl;
        result.data()[len] = '\0'; // Null-terminate the result
        result.resize(len);   // Update the size of the result
        return result;
    }

    // This function should only return the first occurrence of the pattern.
    // All occurrence should be found with the combination of find and substr
    // This function uses Robin-Karp Algorithm.
    [[nodiscard]] size_t find(const char* patternChar, size_t start = 0) const {
        String pattern(patternChar);
        if (pattern.empty()) {
            return start; // Empty pattern matches at the start position
        }

        size_t textLength = this->size();
        size_t patternLength = pattern.size();

        if (start > textLength || textLength - start < patternLength) {
            throw std::out_of_range("String::find start position out of range!");
        }

        // Constants for hash computation
        constexpr size_t HASH_BASE_B = 31;
        constexpr size_t HASH_MODULO_P = 1e9 + 7;

        // Compute the hash for the pattern
        size_t hashPattern = 0;
        for (size_t i = 0; i < patternLength; i++) {
            hashPattern = (hashPattern * HASH_BASE_B + pattern[i]) % HASH_MODULO_P;
        }

        // Compute the hash for the initial window of the text
        size_t hashText = 0;
        for (size_t i = start; i < start + patternLength; i++) {
            hashText = (hashText * HASH_BASE_B + (*this)[i]) % HASH_MODULO_P;
        }

        // Precompute the highest power of HASH_BASE_B modulo HASH_MODULO_P
        size_t highestPower = 1;
        for (size_t i = 0; i < patternLength - 1; i++) {
            highestPower = (highestPower * HASH_BASE_B) % HASH_MODULO_P;
        }

        // Rolling hash to find the pattern
        for (size_t i = start; i <= textLength - patternLength; i++) {
            if (hashText == hashPattern) {
                // Compare the substring to confirm match (handle hash collision)
                bool match = true;
                for (size_t j = 0; j < patternLength; j++) {
                    if ((*this)[i + j] != pattern[j]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    return i; // Match found
                }
            }

            // Update the hash for the next window
            if (i < textLength - patternLength) {
                hashText = (hashText - (*this)[i] * highestPower) % HASH_MODULO_P;
                hashText = (hashText * HASH_BASE_B + (*this)[i + patternLength]) % HASH_MODULO_P;

                // Handle negative hash values
                if (hashText < 0) {
                    hashText += HASH_MODULO_P;
                }
            }
        }

        // Pattern not found
        return String::npos;
    }

};

#endif //STRING_HPP
