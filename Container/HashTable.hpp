#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <functional> // for hashing
#include "Vector.hpp"

template <typename T>
class HashTable {
private:
    struct Node {
        T val;
        Node *next;
        Node(const T& v): val(v), next(nullptr){}
        Node(const T& v, Node *next): val(v), next(next){}
    };

    size_t hashFunction(const T& value) const {
        std::hash<T> hasher;
        return hasher(value) % hashSize;
    }

    Vector<Node*> hashList;
    size_t hashSize;

public:
    HashTable(size_t hashSize): hashSize(hashSize), hashList(hashSize) {}

    void insert(const T& val){
        size_t index = hashFunction(val);
        hashList[index]->next = new Node(val);
    }

    Node* find(const T& val){
        size_t index = hashFunction(val);
        Node* currentNode = hashList[index]->next;
        while(currentNode){
            if(currentNode->val == val)
                return currentNode;
            currentNode = currentNode->next;
        }
        return nullptr;
    }

    void remove(const T& val){
        size_t index = hashFunction(val);
        Node* prevNode = hashList[index];
        Node* currentNode = hashList[index]->next;
        while(currentNode){
            if(currentNode->val == val){
                prevNode->next = currentNode->next;
                delete currentNode;
                return;
            }
            prevNode = prevNode->next;
            currentNode = currentNode->next;
        }
        throw std::out_of_range("Element to be removed not found!");
    }


};

#endif