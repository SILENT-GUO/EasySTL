//
// Created by Zebin Guo on 12/17/24.
//
// 链表加法
// 进阶：单向链表的存储是正向的，即6->1->5 means 615.

#include "LinkedListSum.hpp"
// 链表相加 但是方向是正向的，即3->1->5代表315

void LinkedListSum::padLinkedList(SingleLinkedListNode<int> *&head, int padDepth) {
    if (!head) {
        return;
    }
    while (padDepth > 0) {
        auto* padNode = new SingleLinkedListNode<int>(0);
        padNode->next = head;
        head = padNode;
        padDepth--;
    }
}

int LinkedListSum::LinkedListSumAligned(SingleLinkedListNode<int> *head_1, SingleLinkedListNode<int> *head_2) {
    if (!head_1 || !head_2) {
        return 0;
    }
    const int value = head_1->value + head_2->value + LinkedListSumAligned(head_1->next, head_2->next);
    head_1->value = value % 10;
    return value / 10;

}



SingleLinkedListNode<int>* LinkedListSum::LinkedListSum2_5(SingleLinkedListNode<int> *head_1, SingleLinkedListNode<int> *head_2) {
    if (!head_1) {
        return nullptr;
    }
    if (!head_2) {
        return head_1;
    }

    // use recursion
    SingleLinkedListNode<int> *current_1 = head_1;
    SingleLinkedListNode<int> *current_2 = head_2;
    int offset = 0;

    // first align the two lists.
    while (current_1 && current_2) {
        current_1 = current_1->next;
        current_2 = current_2->next;
    }
    if (current_1) {
        current_1 = current_1->next;
        offset++;
    } else if (current_2) {
        current_2 = current_2->next;
        offset--;
    }
    if (offset > 0) {
        padLinkedList(head_1, offset);
    }else if (offset < 0) {
        padLinkedList(head_2, -offset);
    }
    int carryBit = 0;
    carryBit = LinkedListSumAligned(head_1, head_2);
    if (carryBit > 0) {
        auto *temp = new SingleLinkedListNode<int>(carryBit);
        temp->next = head_1;
        head_1 = temp;
    }

    return head_1;
}
