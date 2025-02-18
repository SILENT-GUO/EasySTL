//
// Created by Zebin Guo on 12/17/24.
//

#ifndef SORTLINKEDLIST_HPP
#define SORTLINKEDLIST_HPP

#include "SingleLinkedList.hpp"

class SortLinkedList {
private:
    static SingleLinkedListNode<int>* mergeSortLinkedList(SingleLinkedListNode<int>* head);
    static SingleLinkedListNode<int>* mergeLinkedList(SingleLinkedListNode<int>* head_1, SingleLinkedListNode<int>* head_2);
public:
    static void sortLinkedList2_4(SingleLinkedListNode<int>* &head);
};

#endif //SORTLINKEDLIST_HPP
