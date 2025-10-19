#ifndef STACK_HPP
#define STACK_HPP

#include <stdexcept>
#include <utility> // for std::move
#include "SingleLinkedList.hpp"

template <typename T>
class Stack {
private:
    SingleLinkedListNode<T>* head_ = nullptr;
    size_t size_ = 0;

    // Helper: deep copy from another stack
    void copyFrom(const Stack& other) {
        if (other.head_ == nullptr) return;
        Stack<T> temp;
        auto* node = other.head_;
        while (node) {
            temp.push(node->value);
            node = node->next;
        }
        while (!temp.empty()) {
            push(temp.top());
            temp.pop();
        }
    }

    void clear() {
        while (head_ != nullptr) {
            pop();
        }
    }

public:
    using value_type = T;
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;

    // Default constructor
    Stack() = default;

    // Destructor
    ~Stack() {
        clear();
    }

    // Copy constructor
    Stack(const Stack& other) {
        copyFrom(other);
    }

    // Move constructor
    Stack(Stack&& other) noexcept
        : head_(other.head_), size_(other.size_) {
        other.head_ = nullptr;
        other.size_ = 0;
    }

    // Copy assignment
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            clear();
            copyFrom(other);
        }
        return *this;
    }

    // Move assignment
    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            clear();
            head_ = other.head_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // Observers
    [[nodiscard]] bool empty() const noexcept {
        return head_ == nullptr;
    }

    [[nodiscard]] size_type size() const noexcept {
        return size_;
    }

    const_reference top() const {
        if (empty()) {
            throw std::runtime_error("Stack is empty! Cannot access top element.");
        }
        return head_->value;
    }

    reference top() {
        if (empty()) {
            throw std::runtime_error("Stack is empty! Cannot access top element.");
        }
        return head_->value;
    }

    // Modifiers
    void push(const T& value) {
        auto* node = new SingleLinkedListNode<T>(value);
        node->next = head_;
        head_ = node;
        ++size_;
    }

    void push(T&& value) {
        auto* node = new SingleLinkedListNode<T>(std::move(value));
        node->next = head_;
        head_ = node;
        ++size_;
    }

    template <typename... Args>
    void emplace(Args&&... args) {
        auto* node = new SingleLinkedListNode<T>(T(std::forward<Args>(args)...));
        node->next = head_;
        head_ = node;
        ++size_;
    }

    void pop() {
        if (empty()) {
            throw std::runtime_error("Stack is empty! Cannot pop element.");
        }
        auto* temp = head_;
        head_ = head_->next;
        delete temp;
        --size_;
    }
};

#endif // STACK_HPP