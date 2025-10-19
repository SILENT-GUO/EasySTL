#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <stdexcept>
#include <utility> // for std::move
#include "SingleLinkedList.hpp"

template <typename T>
class Queue {
private:
    SingleLinkedListNode<T>* head_ = nullptr;
    SingleLinkedListNode<T>* tail_ = nullptr;
    size_t size_ = 0;

    // Helper: deep copy from another queue
    void copyFrom(const Queue& other) {
        if (other.empty()) return;
        auto* node = other.head_;
        while (node) {
            push(node->value);
            node = node->next;
        }
    }

    // Helper: clear all nodes
    void clear() {
        while (!empty()) {
            pop();
        }
    }

public:
    using value_type = T;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;

    // Default constructor
    Queue() = default;

    // Copy constructor
    Queue(const Queue& other) {
        copyFrom(other);
    }

    // Move constructor
    Queue(Queue&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = other.tail_ = nullptr;
        other.size_ = 0;
    }

    // Copy assignment
    Queue& operator=(const Queue& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    // Move assignment
    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // Destructor
    ~Queue() {
        clear();
    }

    // Observers
    [[nodiscard]] bool empty() const noexcept {
        return head_ == nullptr;
    }

    [[nodiscard]] size_type size() const noexcept {
        return size_;
    }

    const_reference front() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty! Cannot access front element.");
        }
        return head_->value; // ✅ corrected from .data to .value
    }

    const_reference back() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty! Cannot access back element.");
        }
        return tail_->value; // ✅ corrected
    }

    // Modifiers
    void push(const T& value) {
        auto* node = new SingleLinkedListNode<T>(value);
        if (tail_) {
            tail_->next = node;
        }
        tail_ = node;
        if (!head_) {
            head_ = node;
        }
        ++size_;
    }

    void push(T&& value) {
        auto* node = new SingleLinkedListNode<T>(std::move(value));
        if (tail_) {
            tail_->next = node;
        }
        tail_ = node;
        if (!head_) {
            head_ = node;
        }
        ++size_;
    }

    template <typename... Args>
    void emplace(Args&&... args) {
        auto* node = new SingleLinkedListNode<T>(T(std::forward<Args>(args)...));
        if (tail_) {
            tail_->next = node;
        }
        tail_ = node;
        if (!head_) {
            head_ = node;
        }
        ++size_;
    }

    void pop() {
        if (empty()) {
            throw std::runtime_error("Queue is empty! Cannot pop element.");
        }
        auto* temp = head_;
        head_ = head_->next;
        delete temp;
        --size_;
        if (!head_) {
            tail_ = nullptr;
        }
    }
};

#endif // QUEUE_HPP