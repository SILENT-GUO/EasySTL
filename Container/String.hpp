//
// Created by Zebin Guo on 12/10/24.
//

#ifndef STRING_HPP
#define STRING_HPP
#include <cstring>
#include "Vector.hpp"
// We define the string to be the child of Vector class.

class String: public Vector<char> {
public:
    String() = default;
    explicit String(const char* cstr) {
        std::cout << "String::String cstr constructor called for " << cstr  << std::endl;
        const size_t len = strlen(cstr);
        this->reserve(len+1);
        memcpy(this->data(), cstr, len+1);
    }
    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        for (size_t i = 0; i < str.size(); i++) {
            os << str[i];
        }
        return os;
    }
};

#endif //STRING_HPP
