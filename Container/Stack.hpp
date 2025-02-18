//
// Created by Zebin Guo on 1/1/25.
//

#ifndef STACK_HPP
#define STACK_HPP
#include <SingleLinkedList.hpp>
// use single linked list as a base class
template <typename T>
class Stack {
private:
    SingleLinkedListNode<T>* head = nullptr;
public:
    // use default constructor.
    Stack() = default;
    ~Stack() {
        while (head != nullptr) {
            pop();
        }
    }
    void pop() {
        if (!head) {
            std::cerr << "Stack is empty! Cannot pop element" << std::endl;
            return;
        }
        auto temp = head;
        head = head->next;
        delete temp;
    }

    const T& top() const {
        if (!head) {
            throw std::runtime_error("Stack is empty! Cannot find the top element");
        }
        return head->value;
    }
    // push to the top of stack
    void push(const T& data) {
        auto node = new SingleLinkedListNode<T>(data);
        node->next = head;
        head = node;
    }

    [[nodiscard]] bool isEmpty() const {
        return head == nullptr;
    }

};

#endif //STACK_HPP
