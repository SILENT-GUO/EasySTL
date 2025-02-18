//
// Created by Zebin Guo on 12/15/24.
//

#include "removeDuplicateNode.hpp"

//编写代码，移除未排序链表中的重复节点。
//进阶：如果不得使用临时缓冲区，该怎么解决

void removeDuplicateNode::removeDuplicateNode_2_1(SingleLinkedListNode<int> *head) {
    SingleLinkedListNode<int> *current = head;
    if (!current) return;
    SingleLinkedListNode<int> *next = current->next;
    if (!next) return;
    while (next) {
        if (current->value == next->value) {
            int val = next->value;
            while (next && next->value == val) {
                next = next->next;
            }
            current->next = next;
            next = next->next;
        }else {
            current = next;
            next = next->next;
        }
    }
}
