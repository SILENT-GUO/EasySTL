//
// Created by Zebin Guo on 12/17/24.
//
#include "connectLinkedList.hpp"

// 寻找出两个链表的相交点

SingleLinkedListNode<int> *ConnectLinkedList::connectLinkedList(SingleLinkedListNode<int> *head_1, SingleLinkedListNode<int> *head_2) {
    if (!head_1 || !head_2) {
        return nullptr;
    }
    SingleLinkedListNode<int> *current_1 = head_1;
    SingleLinkedListNode<int> *current_2 = head_2;

    bool is_changed_1 = false;
    bool is_changed_2 = false;

    while (current_1 && current_2 && current_1 != current_2) {
        current_1 = current_1->next;
        current_2 = current_2->next;
        if (!current_1->next && !is_changed_1) {
            current_1 = head_2;
            is_changed_1 = true;
        }
        if (!current_2->next && !is_changed_2) {
            current_2 = head_1;
            is_changed_2 = true;
        }
    }
    return (current_1 == current_2) ? current_1 : nullptr;
}
