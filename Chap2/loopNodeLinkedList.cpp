//
// Created by Zebin Guo on 12/17/24.
//
#include "loopNodeLinkedList.hpp"

SingleLinkedListNode<int> *LoopNodeLinkedList::LoopNodeLinkedList2_8(SingleLinkedListNode<int> *head) {
    //第一步快慢指针确定是否有环，第二步把慢指针放回head,双指针各走一步，相交点就是loop开始的节点
    //一点简单的数学，画一下图就知道了
    SingleLinkedListNode<int> *fast = head;
    SingleLinkedListNode<int> *slow = head;
    while (fast && fast->next) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) {
            break;
        }
    }
    if (fast != slow) return nullptr;

    slow = head;
    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }
    return slow;
}
