#ifndef SINGLELINKEDLIST_HPP
#define SINGLELINKEDLIST_HPP

#include <iostream>
#include <utility>
#include <stdexcept>
#include "Vector.hpp"

template <typename T>
class SingleLinkedListNode {
public:
    T value;
    SingleLinkedListNode* next;

    explicit SingleLinkedListNode(const T& val, SingleLinkedListNode* nxt = nullptr)
        : value(val), next(nxt) {}

    explicit SingleLinkedListNode(T&& val, SingleLinkedListNode* nxt = nullptr)
        : value(std::move(val)), next(nxt) {}
};

template <typename T>
class SingleLinkedList {
public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

private:
    SingleLinkedListNode<T>* head_ = nullptr;
    size_type size_ = 0;

    void copyFrom(const SingleLinkedList& other) {
        if (other.head_ == nullptr) return;
        head_ = new SingleLinkedListNode<T>(other.head_->value);
        SingleLinkedListNode<T>* curr = head_;
        SingleLinkedListNode<T>* otherCurr = other.head_->next;
        while (otherCurr) {
            curr->next = new SingleLinkedListNode<T>(otherCurr->value);
            curr = curr->next;
            otherCurr = otherCurr->next;
        }
        size_ = other.size_;
    }

    void destroy() {
        while (head_) {
            auto* tmp = head_;
            head_ = head_->next;
            delete tmp;
        }
        size_ = 0;
    }

public:
    // 默认构造
    SingleLinkedList() = default;

    // 拷贝构造
    SingleLinkedList(const SingleLinkedList& other) {
        copyFrom(other);
    }

    // 移动构造
    SingleLinkedList(SingleLinkedList&& other) noexcept
        : head_(other.head_), size_(other.size_) {
        other.head_ = nullptr;
        other.size_ = 0;
    }

    // 拷贝赋值
    SingleLinkedList& operator=(const SingleLinkedList& other) {
        if (this != &other) {
            destroy();
            copyFrom(other);
        }
        return *this;
    }

    // 移动赋值
    SingleLinkedList& operator=(SingleLinkedList&& other) noexcept {
        if (this != &other) {
            destroy();
            head_ = other.head_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    // 从 Vector 构造（支持任意容器，但此处保留 Vector 接口）
    explicit SingleLinkedList(const Vector<T>& vec) {
        for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
            push_front(*it);
        }
    }

    // 析构
    ~SingleLinkedList() {
        destroy();
    }

    // 容器标准接口
    bool empty() const noexcept { return head_ == nullptr; }
    size_type size() const noexcept { return size_; }

    void clear() {
        destroy();
    }

    // 访问
    const_reference front() const {
        if (empty()) throw std::out_of_range("List is empty");
        return head_->value;
    }

    reference front() {
        if (empty()) throw std::out_of_range("List is empty");
        return head_->value;
    }

    const_reference back() const {
        if (empty()) throw std::out_of_range("List is empty");
        auto* node = head_;
        while (node->next) node = node->next;
        return node->value;
    }

    reference back() {
        if (empty()) throw std::out_of_range("List is empty");
        auto* node = head_;
        while (node->next) node = node->next;
        return node->value;
    }

    // 修改
    void push_front(const T& value) {
        head_ = new SingleLinkedListNode<T>(value, head_);
        ++size_;
    }

    void push_front(T&& value) {
        head_ = new SingleLinkedListNode<T>(std::move(value), head_);
        ++size_;
    }

    void push_back(const T& value) {
        if (!head_) {
            push_front(value);
        } else {
            auto* node = head_;
            while (node->next) node = node->next;
            node->next = new SingleLinkedListNode<T>(value);
            ++size_;
        }
    }

    void push_back(T&& value) {
        if (!head_) {
            push_front(std::move(value));
        } else {
            auto* node = head_;
            while (node->next) node = node->next;
            node->next = new SingleLinkedListNode<T>(std::move(value));
            ++size_;
        }
    }

    // 删除第一个匹配值的节点
    void remove(const T& value) {
        if (!head_) return;
        if (head_->value == value) {
            auto* tmp = head_;
            head_ = head_->next;
            delete tmp;
            --size_;
            return;
        }
        auto* prev = head_;
        while (prev->next) {
            if (prev->next->value == value) {
                auto* tmp = prev->next;
                prev->next = tmp->next;
                delete tmp;
                --size_;
                return;
            }
            prev = prev->next;
        }
    }

    SingleLinkedListNode<T>* begin() { return head_; }
    const SingleLinkedListNode<T>* begin() const { return head_; }
    const SingleLinkedListNode<T>* cbegin() const { return head_; }

    std::nullptr_t end() { return nullptr; }
    std::nullptr_t end() const { return nullptr; }
    std::nullptr_t cend() const { return nullptr; }

    void print() const {
        auto* node = head_;
        while (node) {
            std::cout << node->value;
            if (node->next) std::cout << " -> ";
            node = node->next;
        }
        std::cout << '\n';
    }
};

template <typename T>
SingleLinkedListNode<T>* begin(SingleLinkedList<T>& list) { return list.begin(); }

template <typename T>
const SingleLinkedListNode<T>* begin(const SingleLinkedList<T>& list) { return list.begin(); }

template <typename T>
std::nullptr_t end(SingleLinkedList<T>& list) { return list.end(); }

template <typename T>
std::nullptr_t end(const SingleLinkedList<T>& list) { return list.end(); }

#endif // SINGLELINKEDLIST_HPP