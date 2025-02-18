//
// Created by Zebin Guo on 12/17/24.
//
#include "removeKthNode.hpp"
// 删除倒数第k个节点 （注意最后一个是倒数第1个节点）
void RemoveKthNode::removeKthNode2_2(SingleLinkedListNode<int> *head, int k) {
    SingleLinkedListNode<int> *current = head;
    while (current && k > 1) {
        current = current->next;
        k --;
    }
    if (k > 1 || !current) {
        return;
    }
    SingleLinkedListNode<int> *newHead = head;
    SingleLinkedListNode<int> *prevNode = head;
    while (current->next) {
        if (newHead != head) {
            prevNode = prevNode->next;
        }
        current = current->next;
        newHead = newHead->next;
    }
    prevNode->next = newHead->next;
    delete newHead;
}
