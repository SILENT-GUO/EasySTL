#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <type_traits>
#include <initializer_list>
#include <stdexcept>
#include <utility>

template <typename T>
class Vector {
protected:
    T* data_;              // pointer to underlying array
    size_t size_;           // current number of elements
    size_t capacity_;       // total allocated capacity

    void grow() {
        size_t new_capacity = capacity_ * 2;
        T* new_data = new T[new_capacity];

        // Copy existing elements
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = std::move_if_noexcept(data_[i]);
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

public:
    // --- Constructors ---

    Vector() : data_(new T[1]), size_(0), capacity_(1) {}

    explicit Vector(size_t initial_capacity)
        : data_(new T[initial_capacity]), size_(0), capacity_(initial_capacity) {}

    Vector(size_t initial_size, const T& value)
        : data_(new T[initial_size]), size_(initial_size), capacity_(initial_size) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = value;
        }
    }

    Vector(std::initializer_list<T> list)
        : data_(new T[list.size()]), size_(list.size()), capacity_(list.size()) {
        std::copy(list.begin(), list.end(), data_);
    }

    // Copy Constructor
    Vector(const Vector& other)
        : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    // Move Constructor
    Vector(Vector&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    // --- Assignment Operators ---

    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;

        // Allocate new memory
        T* new_data = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; ++i) {
            new_data[i] = other.data_[i];
        }

        delete[] data_;
        data_ = new_data;
        size_ = other.size_;
        capacity_ = other.capacity_;

        return *this;
    }

    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this;

        delete[] data_;

        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }

    // --- Destructor ---
    virtual ~Vector() {
        clear(); // Call destructors for non-trivial types
        delete[] data_;
        data_ = nullptr;
    }

    // --- Element Access ---

    T& at(size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return data_[index];
    }

    const T& at(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return data_[index];
    }

    T& operator[](size_t index) {
        // No bounds check in [], but you can enable in debug mode
        return data_[index];
    }

    const T& operator[](size_t index) const {
        return data_[index];
    }

    T& front() {
        if (empty()) throw std::out_of_range("Vector is empty");
        return data_[0];
    }

    const T& front() const {
        if (empty()) throw std::out_of_range("Vector is empty");
        return data_[0];
    }

    T& back() {
        if (empty()) throw std::out_of_range("Vector is empty");
        return data_[size_ - 1];
    }

    const T& back() const {
        if (empty()) throw std::out_of_range("Vector is empty");
        return data_[size_ - 1];
    }

    T* data() noexcept { return data_; }
    const T* data() const noexcept { return data_; }

    // --- Iterators ---
    T* begin() noexcept { return data_; }
    const T* begin() const noexcept { return data_; }
    const T* cbegin() const noexcept { return data_; }

    T* end() noexcept { return data_ + size_; }
    const T* end() const noexcept { return data_ + size_; }
    const T* cend() const noexcept { return data_ + size_; }

    // --- Capacity ---
    [[nodiscard]] size_t size() const noexcept { return size_; }
    [[nodiscard]] size_t capacity() const noexcept { return capacity_; }
    [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
    [[nodiscard]] bool full() const noexcept { return size_ == capacity_; }

    void reserve(size_t new_capacity) {
        if (new_capacity <= capacity_) return;

        T* new_data = new T[new_capacity];
        try {
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = std::move_if_noexcept(data_[i]);
            }
        } catch (...) {
            delete[] new_data;
            throw;
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    void shrink_to_fit() {
        if (size_ == capacity_) return;

        T* new_data = new T[size_];
        try {
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = std::move_if_noexcept(data_[i]);
            }
        } catch (...) {
            delete[] new_data;
            throw;
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = size_;
    }

    // --- Modifiers ---
    void clear() noexcept {
        if constexpr (!std::is_trivially_destructible_v<T>) {
            for (size_t i = 0; i < size_; ++i) {
                data_[i].~T();
            }
        }
        size_ = 0;
    }

    void resize(size_t new_size) {
        if (new_size == size_) return;

        if (new_size < size_) {
            if constexpr (!std::is_trivially_destructible_v<T>) {
                for (size_t i = new_size; i < size_; ++i) {
                    data_[i].~T();
                }
            }
            size_ = new_size;
        } else {
            if (new_size > capacity_) {
                while (capacity_ < new_size) {
                    capacity_ *= 2;
                }
                T* new_data = new T[capacity_];
                try {
                    for (size_t i = 0; i < size_; ++i) {
                        new_data[i] = std::move_if_noexcept(data_[i]);
                    }
                    // Value-initialize new elements
                    for (size_t i = size_; i < new_size; ++i) {
                        new(&new_data[i]) T(); // placement new
                    }
                } catch (...) {
                    delete[] new_data;
                    throw;
                }

                delete[] data_;
                data_ = new_data;
            } else {
                // No reallocation needed
                for (size_t i = size_; i < new_size; ++i) {
                    new(&data_[i]) T(); // placement new
                }
            }
            size_ = new_size;
        }
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            grow();
            std::cout << "\033[1;32m[Vector Growth]\033[0m Capacity grown to "
                      << capacity_ << " elements!\n";
        }
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ == capacity_) {
            grow();
            std::cout << "\033[1;32m[Vector Growth]\033[0m Capacity grown to "
                      << capacity_ << " elements!\n";
        }
        data_[size_++] = std::move(value);
    }

    template<typename... Args>
    void emplace_back(Args&&... args) {
        if (size_ == capacity_) {
            grow();
            std::cout << "\033[1;32m[Vector Growth]\033[0m Capacity grown to "
                      << capacity_ << " elements!\n";
        }
        new(&data_[size_]) T(std::forward<Args>(args)...);
        ++size_;
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::out_of_range("Vector::pop_back(): empty vector");
        }
        --size_;
        if constexpr (!std::is_trivially_destructible_v<T>) {
            data_[size_].~T();
        }
    }

    template<typename U>
    friend bool operator==(const Vector& a, const Vector<U>& b) {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            if (a.data_[i] != b.data_[i]) return false;
        }
        return true;
    }

    template<typename U>
    friend bool operator!=(const Vector& a, const Vector<U>& b) {
        return !(a == b);
    }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vec) {
        os << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            os << vec.data_[i];
            if (i != vec.size() - 1) os << ", ";
        }
        os << "]";
        return os;
    }
};

#endif