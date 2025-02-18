//
// Created by Zebin Guo on 1/1/25.
//

#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <SingleLinkedList.hpp>

template <typename T>
class Queue {
private:
    SingleLinkedListNode<T>* head = nullptr; // Points to the front of the queue
    SingleLinkedListNode<T>* tail = nullptr; // Points to the rear of the queue
    size_t count = 0;                        // Stores the number of elements in the queue

public:
    // Constructor
    Queue() = default;

    // Destructor to clean up memory
    ~Queue() {
        while (!empty()) {
            pop();
        }
    }

    // Check if the queue is empty
    [[nodiscard]] bool empty() const {
        return head == nullptr;
    }

    // Return the number of elements in the queue
    [[nodiscard]] size_t size() const {
        return count;
    }

    // Get a reference to the front element of the queue
    const T& front() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty! Cannot access front element.");
        }
        return head->data;
    }

    // Get a reference to the back element of the queue
    const T& back() const {
        if (empty()) {
            throw std::runtime_error("Queue is empty! Cannot access back element.");
        }
        return tail->data;
    }

    // Add an element to the rear of the queue
    void push(const T& value) {
        auto node = new SingleLinkedListNode<T>(value);
        if (tail) {
            tail->next = node;
        }
        tail = node;

        // If the queue was empty, set head to the new node
        if (!head) {
            head = node;
        }
        ++count;
    }

    // Remove the front element of the queue
    void pop() {
        if (empty()) {
            throw std::runtime_error("Queue is empty! Cannot pop element.");
        }
        auto temp = head;
        head = head->next;
        delete temp;

        // If the queue becomes empty, set tail to nullptr
        if (!head) {
            tail = nullptr;
        }

        --count;
    }
};


#endif //QUEUE_HPP
