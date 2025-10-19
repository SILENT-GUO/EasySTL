#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <iostream>
#include <memory>
#include <iterator>

template <typename T, typename Allocator = std::allocator<T>>
class Vector
{
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T &;
    using const_reference = const T &;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator = T *;
    using const_iterator = const T *;

private:
    T *data_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
    Allocator alloc_;

    template <typename... Args>
    void construct_at(T *p, Args &&...args)
    {
        std::allocator_traits<Allocator>::construct(
            alloc_, p, std::forward<Args>(args)...);
    }

    void destroy_at(T *p) noexcept
    {
        if constexpr (!std::is_trivially_destructible_v<T>)
        {
            std::allocator_traits<Allocator>::destroy(alloc_, p);
        }
    }

    void destroy_range(T *first, T *last) noexcept
    {
        for (; first != last; ++first)
        {
            destroy_at(first);
        }
    }

    void grow()
    {
        size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        T *new_data = alloc_.allocate(new_capacity);

        T *dest = new_data;
        T *src = data_;
        size_t constructed = 0;
        try
        {
            for (size_t i = 0; i < size_; ++i)
            {
                construct_at(dest + i, std::move_if_noexcept(src[i]));
                ++constructed;
            }
        }
        catch (...)
        {
            destroy_range(new_data, new_data + constructed);
            alloc_.deallocate(new_data, new_capacity);
            throw;
        }

        destroy_range(data_, data_ + size_);
        if (data_)
            alloc_.deallocate(data_, capacity_);

        data_ = new_data;
        capacity_ = new_capacity;
    }

    template <typename U>
    iterator insert_impl(const_iterator pos, U &&value)
    {
        size_t offset = pos - cbegin();
        T tmp = std::forward<U>(value);
        if (size_ == capacity_)
        {
            grow();
            pos = cbegin() + offset;
        }

        T *p = data_ + offset;

        if (offset == size_)
        {
            construct_at(p, std::move(tmp));
        }
        else
        {
            construct_at(data_ + size_, std::move(data_[size_ - 1]));
            for (size_t i = size_ - 1; i > offset; --i)
            {
                data_[i] = std::move(data_[i - 1]);
            }
            *p = std::move(tmp);
        }
        ++size_;
        return begin() + offset;
    }

public:
    Vector() = default;

    explicit Vector(size_t count, const T &value, const Allocator &alloc = Allocator())
        : alloc_(alloc)
    {
        reserve(count);
        for (size_t i = 0; i < count; ++i)
        {
            construct_at(data_ + i, value);
            ++size_;
        }
    }

    explicit Vector(size_t count, const Allocator &alloc = Allocator())
        : alloc_(alloc)
    {
        reserve(count);
        for (size_t i = 0; i < count; ++i)
        {
            construct_at(data_ + i);
            ++size_;
        }
    }

    template <typename InputIt>
    Vector(InputIt first, InputIt last, const Allocator &alloc = Allocator())
        : alloc_(alloc)
    {
        while (first != last)
        {
            push_back(*first);
            ++first;
        }
    }

    Vector(std::initializer_list<T> ilist, const Allocator &alloc = Allocator())
        : Vector(ilist.begin(), ilist.end(), alloc) {}

    Vector(const Vector &other)
        : alloc_(std::allocator_traits<Allocator>::select_on_container_copy_construction(other.alloc_))
    {
        reserve(other.size_);
        for (const auto &elem : other)
        {
            push_back(elem);
        }
    }

    Vector(Vector &&other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_), alloc_(std::move(other.alloc_))
    {
        other.data_ = nullptr;
        other.size_ = other.capacity_ = 0;
    }

    Vector &operator=(const Vector &other)
    {
        if (this != &other)
        {
            clear();
            alloc_ = std::allocator_traits<Allocator>::select_on_container_copy_construction(other.alloc_);
            reserve(other.size_);
            for (const auto &elem : other)
            {
                push_back(elem);
            }
        }
        return *this;
    }

    Vector &operator=(Vector &&other) noexcept
    {
        if (this != &other)
        {
            clear();
            if (data_)
                alloc_.deallocate(data_, capacity_);
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            alloc_ = std::move(other.alloc_);
            other.data_ = nullptr;
            other.size_ = other.capacity_ = 0;
        }
        return *this;
    }

    ~Vector()
    {
        clear();
        if (data_)
            alloc_.deallocate(data_, capacity_);
    }

    void assign(size_t count, const T &value)
    {
        clear();
        reserve(count);
        for (size_t i = 0; i < count; ++i)
        {
            push_back(value);
        }
    }

    template <typename InputIt>
    void assign(InputIt first, InputIt last)
    {
        clear();
        while (first != last)
        {
            push_back(*first);
            ++first;
        }
    }

    void assign(std::initializer_list<T> ilist)
    {
        assign(ilist.begin(), ilist.end());
    }

    allocator_type get_allocator() const { return alloc_; }

    // Element access
    T &at(size_t pos)
    {
        if (pos >= size_)
            throw std::out_of_range("Vector::at");
        return data_[pos];
    }
    const T &at(size_t pos) const
    {
        if (pos >= size_)
            throw std::out_of_range("Vector::at");
        return data_[pos];
    }

    T &operator[](size_t pos) { return data_[pos]; }
    const T &operator[](size_t pos) const { return data_[pos]; }

    T &front() { return data_[0]; }
    const T &front() const { return data_[0]; }

    T &back() { return data_[size_ - 1]; }
    const T &back() const { return data_[size_ - 1]; }

    T *data() noexcept { return data_; }
    const T *data() const noexcept { return data_; }

    // Iterators
    iterator begin() noexcept { return data_; }
    const_iterator begin() const noexcept { return data_; }
    const_iterator cbegin() const noexcept { return data_; }

    iterator end() noexcept { return data_ + size_; }
    const_iterator end() const noexcept { return data_ + size_; }
    const_iterator cend() const noexcept { return data_ + size_; }

    // Capacity
    bool empty() const noexcept { return size_ == 0; }
    size_t size() const noexcept { return size_; }
    size_t max_size() const noexcept { return alloc_.max_size(); }
    size_t capacity() const noexcept { return capacity_; }

    void reserve(size_t new_cap)
    {
        if (new_cap <= capacity_)
            return;
        T *new_data = alloc_.allocate(new_cap);
        T *dest = new_data;
        try
        {
            for (size_t i = 0; i < size_; ++i)
            {
                construct_at(dest + i, std::move_if_noexcept(data_[i]));
            }
        }
        catch (...)
        {
            destroy_range(new_data, new_data + size_);
            alloc_.deallocate(new_data, new_cap);
            throw;
        }
        destroy_range(data_, data_ + size_);
        if (data_)
            alloc_.deallocate(data_, capacity_);
        data_ = new_data;
        capacity_ = new_cap;
    }

    void shrink_to_fit()
    {
        if (size_ == capacity_)
            return;
        if (size_ == 0)
        {
            if (data_)
                alloc_.deallocate(data_, capacity_);
            data_ = nullptr;
            capacity_ = 0;
            return;
        }
        T *new_data = alloc_.allocate(size_);
        try
        {
            for (size_t i = 0; i < size_; ++i)
            {
                construct_at(new_data + i, std::move_if_noexcept(data_[i]));
            }
        }
        catch (...)
        {
            destroy_range(new_data, new_data + size_);
            alloc_.deallocate(new_data, size_);
            throw;
        }
        destroy_range(data_, data_ + size_);
        alloc_.deallocate(data_, capacity_);
        data_ = new_data;
        capacity_ = size_;
    }

    // Modifiers
    void clear() noexcept
    {
        destroy_range(data_, data_ + size_);
        size_ = 0;
    }

    void resize(size_t new_size)
    {
        if (new_size < size_)
        {
            destroy_range(data_ + new_size, data_ + size_);
            size_ = new_size;
        }
        else if (new_size > size_)
        {
            reserve(new_size);
            for (size_t i = size_; i < new_size; ++i)
            {
                construct_at(data_ + i);
            }
            size_ = new_size;
        }
    }

    void resize(size_t new_size, const T &value)
    {
        if (new_size < size_)
        {
            destroy_range(data_ + new_size, data_ + size_);
            size_ = new_size;
        }
        else if (new_size > size_)
        {
            reserve(new_size);
            for (size_t i = size_; i < new_size; ++i)
            {
                construct_at(data_ + i, value);
            }
            size_ = new_size;
        }
    }

    void push_back(const T &value)
    {
        if (size_ == capacity_)
            grow();
        construct_at(data_ + size_, value);
        ++size_;
    }

    void push_back(T &&value)
    {
        if (size_ == capacity_)
            grow();
        construct_at(data_ + size_, std::move(value));
        ++size_;
    }

    template <typename... Args>
    void emplace_back(Args &&...args)
    {
        if (size_ == capacity_)
            grow();
        construct_at(data_ + size_, std::forward<Args>(args)...);
        ++size_;
    }

    void pop_back()
    {
        if (size_ == 0)
            return;
        --size_;
        destroy_at(data_ + size_);
    }

    iterator insert(const_iterator pos, const T &value)
    {
        return insert_impl(pos, value);
    }

    iterator insert(const_iterator pos, T &&value)
    {
        return insert_impl(pos, std::move(value));
    }

    iterator erase(const_iterator pos)
    {
        return erase(pos, pos + 1);
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        size_t offset = std::distance(cbegin(), first);
        size_t count = std::distance(first, last);
        iterator it = begin() + offset;
        for (size_t i = offset; i < size_ - count; ++i)
        {
            data_[i] = std::move(data_[i + count]);
        }
        destroy_range(data_ + size_ - count, data_ + size_);
        size_ -= count;
        return it;
    }

    void swap(Vector &other) noexcept
    {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(alloc_, other.alloc_);
    }

    // Comparison operators
    friend bool operator==(const Vector &a, const Vector &b)
    {
        return a.size_ == b.size_ && std::equal(a.begin(), a.end(), b.begin());
    }

    friend bool operator!=(const Vector &a, const Vector &b)
    {
        return !(a == b);
    }

    friend bool operator<(const Vector &a, const Vector &b)
    {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }

    friend bool operator<=(const Vector &a, const Vector &b) { return !(b < a); }
    friend bool operator>(const Vector &a, const Vector &b) { return b < a; }
    friend bool operator>=(const Vector &a, const Vector &b) { return !(a < b); }

    // Stream output
    template <typename U, typename A>
    friend std::ostream &operator<<(std::ostream &os, const Vector<U, A> &v)
    {
        os << "[";
        for (size_t i = 0; i < v.size(); ++i)
        {
            os << v[i];
            if (i != v.size() - 1)
                os << ", ";
        }
        os << "]";
        return os;
    }
};

#endif