#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <functional>
#include <stdexcept>
#include "Vector.hpp"

template <typename T>
class HashTable {
private:
    struct Node {
        T val;
        Node* next;
        Node(const T& v, Node* n = nullptr) : val(v), next(n) {}
    };

    Vector<Node*> buckets_;

    size_t hashFunction(const T& value) const {
        std::hash<T> hasher;
        return hasher(value) % buckets_.size();
    }

    void clear() {
        for (size_t i = 0; i < buckets_.size(); ++i) {
            Node* curr = buckets_[i];
            while (curr) {
                Node* next = curr->next;
                delete curr;
                curr = next;
            }
            buckets_[i] = nullptr;
        }
    }

public:
    explicit HashTable(size_t initialBucketCount = 16) : buckets_(initialBucketCount) {
        for (size_t i = 0; i < buckets_.size(); ++i) {
            buckets_[i] = nullptr;
        }
    }

    HashTable(const HashTable& other) : buckets_(other.buckets_.size()) {
        for (size_t i = 0; i < buckets_.size(); ++i) {
            buckets_[i] = nullptr;
        }
        try {
            for (size_t i = 0; i < other.buckets_.size(); ++i) {
                Node* curr = other.buckets_[i];
                while (curr) {
                    insert(curr->val);
                    curr = curr->next;
                }
            }
        } catch (...) {
            clear();
            throw;
        }
    }

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            HashTable tmp(other);
            swap(tmp);
        }
        return *this;
    }

    HashTable(HashTable&& other) noexcept
        : buckets_(std::move(other.buckets_)) {}

    HashTable& operator=(HashTable&& other) noexcept {
        if (this != &other) {
            clear();
            buckets_ = std::move(other.buckets_);
        }
        return *this;
    }

    ~HashTable() {
        clear();
    }

    void swap(HashTable& other) noexcept {
        buckets_.swap(other.buckets_);
    }

    void insert(const T& val) {
        size_t index = hashFunction(val);
        buckets_[index] = new Node(val, buckets_[index]);
    }

    bool contains(const T& val) const {
        size_t index = hashFunction(val);
        Node* curr = buckets_[index];
        while (curr) {
            if (curr->val == val) return true;
            curr = curr->next;
        }
        return false;
    }

    void remove(const T& val) {
        size_t index = hashFunction(val);
        Node* prev = nullptr;
        Node* curr = buckets_[index];
        while (curr) {
            if (curr->val == val) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    buckets_[index] = curr->next;
                }
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
        throw std::out_of_range("Element to be removed not found!");
    }

    size_t bucketCount() const {
        return buckets_.size();
    }

    size_t size() const {
        size_t total = 0;
        for (size_t i = 0; i < buckets_.size(); ++i) {
            Node* curr = buckets_[i];
            while (curr) {
                ++total;
                curr = curr->next;
            }
        }
        return total;
    }

    bool empty() const {
        return size() == 0;
    }
};

#endif // HASHTABLE_HPP