#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>
#include <cstring>
#include <string>
#include <stdexcept>
#include <concepts>
#include <algorithm>
#include "Vector.hpp" // 假设 Vector<T> 已正确实现 insert/assign 等

// C++20 concept for arithmetic types
template <typename T>
concept arithmetic = std::is_arithmetic_v<T>;

class String
{
private:
    static constexpr size_t HASH_BASE_B = 31;
    static constexpr size_t HASH_MODULO_P = 1000000007;

    Vector<char> data_;

public:
    // STL-compatible iterator types
    using iterator = typename Vector<char>::iterator;
    using const_iterator = typename Vector<char>::const_iterator;

    static constexpr int npos = -1;

    // --- Constructors ---
    String()
    {
        data_.push_back('\0');
    }

    explicit String(const char *cstr)
    {
        if (cstr == nullptr)
        {
            data_.push_back('\0');
            return;
        }
        size_t len = std::strlen(cstr);
        data_.assign(cstr, cstr + len);
        data_.push_back('\0');
    }

    String(size_t n, char ch)
    {
        data_.assign(n, ch);
        data_.push_back('\0');
    }

    explicit String(const Vector<char> &vec)
    {
        data_.assign(vec.begin(), vec.end());
        data_.push_back('\0');
    }

    String(const String &other) : data_(other.data_) {}

    String(String &&other) noexcept : data_(std::move(other.data_)) {}

    // --- Assignment operators ---
    String &operator=(const String &other)
    {
        if (this != &other)
        {
            data_ = other.data_;
        }
        return *this;
    }

    String &operator=(String &&other) noexcept
    {
        if (this != &other)
        {
            data_ = std::move(other.data_);
        }
        return *this;
    }

    // --- Destructor ---
    ~String() = default;

    // --- Capacity ---
    size_t size() const noexcept
    {
        return data_.size() - 1; // exclude '\0'
    }

    size_t length() const noexcept
    {
        return size();
    }

    bool empty() const noexcept
    {
        return size() == 0;
    }

    size_t capacity() const noexcept
    {
        return data_.capacity() - 1; // exclude '\0' slot
    }

    void reserve(size_t newCap)
    {
        data_.reserve(newCap + 1); // +1 for null terminator
    }

    void clear()
    {
        data_.clear();
        data_.push_back('\0');
    }

    // --- Element access ---
    char &operator[](size_t pos)
    {
        return data_[pos]; // no bounds check
    }

    const char &operator[](size_t pos) const
    {
        return data_[pos];
    }

    char &at(size_t pos)
    {
        if (pos >= size())
            throw std::out_of_range("String::at");
        return data_[pos];
    }

    const char &at(size_t pos) const
    {
        if (pos >= size())
            throw std::out_of_range("String::at");
        return data_[pos];
    }

    // --- Data access ---
    const char *c_str() const noexcept
    {
        return data_.data();
    }

    const char *data() const noexcept
    {
        return c_str();
    }

    // --- Modifiers ---
    void push_back(char ch)
    {
        data_.pop_back(); // remove '\0'
        data_.push_back(ch);
        data_.push_back('\0');
    }

    String &operator+=(char ch)
    {
        push_back(ch);
        return *this;
    }

    String &operator+=(const String &other)
    {
        if (other.empty())
            return *this;
        data_.pop_back();
        this->insert(data_.end(), other.data_.begin(), other.data_.end() - 1);
        data_.push_back('\0');
        return *this;
    }

    String &operator+=(const char *cstr)
    {
        if (cstr == nullptr)
            return *this;
        String tmp(cstr);
        return *this += tmp;
    }

    // --- STL-compatible insert (core) ---

    // 1. insert(p, ch)
    iterator insert(const_iterator p, char ch)
    {
        if (p < cbegin() || p > cend())
        {
            throw std::out_of_range("String::insert: iterator out of range");
        }
        data_.pop_back(); // remove '\0'
        auto it = data_.insert(p, ch);
        data_.push_back('\0');
        return it;
    }

    // 2. insert(p, count, ch)
    iterator insert(const_iterator p, size_t count, char ch)
    {
        if (p < cbegin() || p > cend())
        {
            throw std::out_of_range("String::insert: iterator out of range");
        }
        if (count == 0)
        {
            return const_cast<iterator>(p); // no-op, return p as iterator
        }

        data_.pop_back(); // remove '\0'

        // Insert 'count' copies of 'ch' one by one at position p
        // Note: after first insert, p may be invalidated if reallocation happened!
        // So we track offset instead.
        size_t offset = p - cbegin();
        for (size_t i = 0; i < count; ++i)
        {
            // Recompute position after possible reallocation
            auto pos = data_.begin() + offset + i;
            data_.insert(pos, ch);
        }

        data_.push_back('\0');
        return data_.begin() + offset; // return iterator to first inserted char
    }

    template <typename InputIt>
    iterator insert(const_iterator p, InputIt first, InputIt last)
    {
        if (p < cbegin() || p > cend())
        {
            throw std::out_of_range("String::insert: iterator out of range");
        }

        // Handle empty range
        if (first == last)
        {
            return const_cast<iterator>(p);
        }

        data_.pop_back(); // remove '\0'

        size_t offset = p - cbegin();
        size_t inserted = 0;

        try
        {
            while (first != last)
            {
                auto pos = data_.begin() + offset + inserted;
                data_.insert(pos, *first);
                ++inserted;
                ++first;
            }
        }
        catch (...)
        {
            data_.push_back('\0');
            throw;
        }

        data_.push_back('\0');
        return data_.begin() + offset;
    }

    String &insert(size_t pos, const String &str)
    {
        if (pos > size())
        {
            throw std::out_of_range("String::insert: pos out of range");
        }
        insert(cbegin() + pos, str.data_.begin(), str.data_.end() - 1);
        return *this;
    }

    String &insert(size_t pos, const char *s)
    {
        if (s == nullptr)
        {
            throw std::invalid_argument("String::insert: null pointer");
        }
        if (pos > size())
        {
            throw std::out_of_range("String::insert: pos out of range");
        }
        size_t len = std::strlen(s);
        insert(cbegin() + pos, s, s + len);
        return *this;
    }

    String &insert(size_t pos, const char *s, size_t count)
    {
        if (s == nullptr && count > 0)
        {
            throw std::invalid_argument("String::insert: null pointer with count > 0");
        }
        if (pos > size())
        {
            throw std::out_of_range("String::insert: pos out of range");
        }
        insert(cbegin() + pos, s, s + count);
        return *this;
    }

    String &insert(size_t pos, size_t count, char ch)
    {
        if (pos > size())
        {
            throw std::out_of_range("String::insert: pos out of range");
        }
        insert(cbegin() + pos, count, ch);
        return *this;
    }

    // --- Substring ---
    [[nodiscard]] String substr(size_t pos = 0, size_t len = npos) const
    {
        if (pos > size())
        {
            throw std::out_of_range("String::substr");
        }
        size_t rlen = std::min(len, size() - pos);
        String result;
        result.data_.assign(data_.begin() + pos, data_.begin() + pos + rlen);
        result.data_.push_back('\0');
        return result;
    }

    // --- Find ---
    [[nodiscard]] int find(const char *s, size_t pos = 0) const
    {
        if (s == nullptr)
            return npos;
        size_t patternLen = std::strlen(s);
        if (patternLen == 0)
            return static_cast<int>(pos);
        if (pos > size() || size() - pos < patternLen)
            return npos;

        for (size_t i = pos; i <= size() - patternLen; ++i)
        {
            if (std::memcmp(data_.data() + i, s, patternLen) == 0)
            {
                return static_cast<int>(i);
            }
        }
        return npos;
    }

    [[nodiscard]] int find(const String &str, size_t pos = 0) const
    {
        return find(str.c_str(), pos);
    }

    [[nodiscard]] int find(char ch, size_t pos = 0) const
    {
        for (size_t i = pos; i < size(); ++i)
        {
            if (data_[i] == ch)
                return static_cast<int>(i);
        }
        return npos;
    }

    // --- Iterators ---
    iterator begin() noexcept { return data_.begin(); }
    const_iterator begin() const noexcept { return data_.begin(); }
    const_iterator cbegin() const noexcept { return data_.cbegin(); }

    iterator end() noexcept { return data_.end() - 1; } // exclude '\0'
    const_iterator end() const noexcept { return data_.end() - 1; }
    const_iterator cend() const noexcept { return data_.cend() - 1; }

    // --- Friends ---
    friend std::ostream &operator<<(std::ostream &os, const String &str)
    {
        os << str.c_str();
        return os;
    }

    friend String operator+(const String &lhs, const String &rhs)
    {
        String result = lhs;
        result += rhs;
        return result;
    }

    friend String operator+(const String &lhs, const char *rhs)
    {
        String result = lhs;
        result += rhs;
        return result;
    }

    friend String operator+(const char *lhs, const String &rhs)
    {
        String result(lhs);
        result += rhs;
        return result;
    }

    // --- Utility ---
    template <arithmetic T>
    static String to_String(T value)
    {
        return String(std::to_string(value).c_str());
    }
};

#endif // STRING_HPP