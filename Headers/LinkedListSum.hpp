//
// Created by Zebin Guo on 12/17/24.
//

#ifndef LINKEDLISTSUM_HPP
#define LINKEDLISTSUM_HPP

#include "SingleLinkedList.hpp"

class LinkedListSum {
private:
    // we sum head_2 to head_1 here.
    static int LinkedListSumAligned(SingleLinkedListNode<int>* head_1, SingleLinkedListNode<int>* head_2);
    static void padLinkedList(SingleLinkedListNode<int>*& head, int padDepth);
public:
    static SingleLinkedListNode<int> * LinkedListSum2_5(SingleLinkedListNode<int>* head_1, SingleLinkedListNode<int>* head_2);
};

#endif //LINKEDLISTSUM_HPP
