//
// Created by Zebin Guo on 12/14/24.
//

#ifndef SINGLELINKEDLIST_HPP
#define SINGLELINKEDLIST_HPP

#include <iostream>
#include "Vector.hpp"

template<typename T>
class SingleLinkedListNode {
public:
    SingleLinkedListNode *next;
    T value;
    explicit SingleLinkedListNode(T value) {
        //一个参数的构造函数可能会隐式转换
        //explicit 阻止隐式转换
        this->value = value;
        this->next = nullptr;
    }

    SingleLinkedListNode(T value, SingleLinkedListNode *next) {
        this->value = value;
        this->next = next;
    }


};

template<typename T>
class SingleLinkedList {
public:
    SingleLinkedListNode<T> *head;
    SingleLinkedList(): head(nullptr) {}
    explicit SingleLinkedList(const SingleLinkedListNode<T> &node) {
        this->head = new SingleLinkedListNode<T>(node.value);
    }

    //construct from list
    explicit SingleLinkedList(const Vector<T> vector) {
        if (vector.empty()) {
            std::cerr << "Vector is empty" << std::endl;
        }
        this->head = new SingleLinkedListNode<T>(vector[0]);
        SingleLinkedListNode<T> *current = this->head;
        for (int i = 1; i < vector.size(); i++) {
            current->next = new SingleLinkedListNode<T>(vector[i]);
            current = current->next;
        }
    }

    void push_front(T value) {
        auto *node = new SingleLinkedListNode<T>(value, head);
        head = node;
    }

    void push(T value) {
        if (!head) {
            head = new SingleLinkedListNode<T>(value);
            return;
        }
        auto *node = head;
        while (node->next) {
            node = node->next;
        }
        node->next = new SingleLinkedListNode<T>(value);
    }

    bool isEmpty() {
        return head == nullptr;
    }

    T front() {
        return head->value;
    }

    T back() {
        auto *node = head;
        while (node->next) {
            node = node->next;
        }
        return node->value;
    }

    void deleteNodeByValue(T value) {
        // only delete the first element of value encountered.
        auto *node = head;
        while (node) {
            if (node->value == value) {
                auto *tmp = node->next;
                if (node == head) {
                    head = tmp->next;
                    delete tmp;
                    return;
                }
                node->next = tmp->next;
                delete tmp;
                return;
            }
            node = node->next;
        }
    }

    void printLinkedList() {
        auto *node = head;
        while (node) {
            std::cout << node->value;
            node = node->next;
            if (node) {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
    }
};

#endif //SINGLELINKEDLIST_HPP
