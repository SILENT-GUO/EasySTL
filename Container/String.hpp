//
// Created by Zebin Guo on 12/10/24.
//

#ifndef STRING_HPP
#define STRING_HPP

#include <cstring>
#include <concepts>
#include "Vector.hpp"

// Define the arithmetic concept
template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

// String class inheriting from Vector<char>
class String : public Vector<char> {
private:
    static constexpr size_t HASH_BASE_B = 31; // Updated to match typical Robin-Karp implementation
    static constexpr size_t HASH_MODULO_P = 1000000007; // Use an integer for modulo

public:
    static constexpr int npos = -1;

    // Default Constructor
    String() = default; // Inherits Vector<char>() constructor

    // Constructor from C-string
    explicit String(const char* cstr) : Vector<char>() {
        if (cstr == nullptr) {
            // Handle null pointer input gracefully
            this->numElements = 0;
            this->reserve(1);
            (*this)[0] = '\0'; // Ensure it's a valid empty string
            return;
        }

        const size_t len = std::strlen(cstr); // Length of the input string (does not include null terminator)
        this->reserve(len + 1); // Reserve space for characters + null terminator
        std::copy(cstr, cstr + len, this->begin()); // Copy characters
        this->numElements = len; // Set the size of the string
        (*this)[len] = '\0'; // Ensure null termination
    }


    // Constructor with size and initial value
    String(const size_t size, const char initialValue) : Vector<char>(size+1, size, initialValue) {
        // Ensure null termination if needed
        if (size > 0) {
            (*this)[size] = '\0';
        }
    }

    // Copy Constructor
    String(const String& other) : Vector<char>(other) {}

    // Move Constructor
    String(String&& other) noexcept : Vector<char>(std::move(other)) {}

    // Copy Assignment Operator
    String& operator=(const String& other) {
        Vector<char>::operator=(other);
        return *this;
    }

    // Move Assignment Operator
    String& operator=(String&& other) noexcept {
        Vector<char>::operator=(std::move(other));
        return *this;
    }

    // Destructor
    ~String() = default; // Inherits Vector<char>'s destructor

    // Overloaded Output Operator
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        for (size_t i = 0; i < str.size(); i++) {
            os << str[i];
        }
        return os;
    }

    // Substring Method
    [[nodiscard]] String substr(size_t start, int end = String::npos) const {
        if (start >= this->size()) {
            throw std::out_of_range("String::substr start position out of range!");
        }
        if (end == String::npos || end > this->size()) {
            end = this->size();
        }

        const size_t len = end - start;
        String result;
        result.reserve(len + 1); // +1 for null terminator
        std::copy_n(this->data() + start, len, result.begin());
        result.numElements = len;
        result[len] = '\0';
        return result;
    }

    // Robin-Karp Algorithm for Find
    [[nodiscard]] int find(const char* patternChar, size_t start = 0) const {
        String pattern(patternChar); // Wrap the pattern as a String for consistency
        if (pattern.empty()) {
            return npos;
        }

        size_t textLength = this->size();
        size_t patternLength = pattern.size();

        if (start >= textLength || textLength - start < patternLength) {
            // Start position is out of range or remaining text is shorter than pattern
            return String::npos;
        }

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
                // Rolling hash: remove the leading character and add the trailing character
                hashText = (hashText + HASH_MODULO_P - ((*this)[i] * highestPower) % HASH_MODULO_P) % HASH_MODULO_P;
                hashText = (hashText * HASH_BASE_B + (*this)[i + patternLength]) % HASH_MODULO_P;
            }
        }

        // Pattern not found
        return String::npos;
    }

    // c_str Method ensuring null termination
    [[nodiscard]] const char* c_str() const {
        // Ensure there's a null terminator
        if (this->size() == this->capacity()) {
            const_cast<String*>(this)->reserve(this->size() + 1);
        }
        (*const_cast<String*>(this))[this->size()] = '\0';
        return this->begin();
    }

    // Overloaded Addition Operator
    String operator+(const String& other) const {
        String result;
        const size_t newLength = this->size() + other.size();
        result.reserve(newLength + 1); // +1 for null terminator

        std::ranges::copy(*this, result.begin());
        std::ranges::copy(other, result.begin() + this->size());

        result.numElements = newLength;
        result[newLength] = '\0';
        return result;
    }

    // Overloaded Addition Assignment Operator (String)
    void operator+=(const String& other) {
        size_t originalSize = this->size();
        size_t newSize = originalSize + other.size();

        // Ensure sufficient capacity
        this->reserve(newSize + 1); // +1 for null terminator

        // Resize to include the new data
        this->numElements = newSize;

        // Copy the data from the other string
        std::copy(other.begin(), other.end(), this->begin() + originalSize);

        // Ensure null termination
        (*this)[newSize] = '\0';
    }

    // Overloaded Addition Assignment Operator (C-string)
    void operator+=(const char* other) {
        if (other == nullptr) return;

        size_t otherLength = std::strlen(other);
        size_t originalSize = this->size();
        size_t newSize = originalSize + otherLength;

        // Ensure sufficient capacity
        this->reserve(newSize + 1); // +1 for null terminator

        // Resize to include the new data
        this->numElements = newSize;

        // Copy the data from the C-string
        std::copy(other, other + otherLength, this->begin() + originalSize);

        // Ensure null termination
        (*this)[newSize] = '\0';
    }

    // Static Method to Convert Arithmetic Types to String
    template <typename T>
    requires arithmetic<T>
    static String to_String(T value) {
        const std::string stringStr = std::to_string(value);
        return String(stringStr.c_str());
    }
};

#endif // STRING_HPP
