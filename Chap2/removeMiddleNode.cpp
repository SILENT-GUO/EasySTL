//
// Created by Zebin Guo on 12/17/24.
//
#include "removeMiddleNode.hpp"

void RemoveMiddleNode::RemoveMiddleNode2_3(SingleLinkedListNode<int> *node) {
    if (node == nullptr) return;
    if (node->next == nullptr) {
        delete node;
        return;
    }
    SingleLinkedListNode<int> *temp = node->next;

    node->value = node->next->value;
    node->next = node->next->next;

    delete temp;



}
