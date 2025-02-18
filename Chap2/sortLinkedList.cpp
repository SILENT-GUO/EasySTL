#include "sortLinkedList.hpp"

// Merges two sorted linked lists and returns the merged head
SingleLinkedListNode<int>* SortLinkedList::mergeLinkedList(SingleLinkedListNode<int>* head_1, SingleLinkedListNode<int>* head_2) {
    auto* dummy = new SingleLinkedListNode<int>(0);
    auto* cur = dummy;

    // Merge two sorted lists
    while (head_1 && head_2) {
        if (head_1->value < head_2->value) {
            cur->next = head_1;
            head_1 = head_1->next;
        } else {
            cur->next = head_2;
            head_2 = head_2->next;
        }
        cur = cur->next;
    }

    // Append the remaining nodes
    if (head_1) cur->next = head_1;
    if (head_2) cur->next = head_2;

    SingleLinkedListNode<int>* result = dummy->next;
    delete dummy;
    return result;
}

// Merge Sort for linked list
SingleLinkedListNode<int>* SortLinkedList::mergeSortLinkedList(SingleLinkedListNode<int>* head) {
    if (!head || !head->next) {
        return head;  // Base case: single node or empty list
    }

    // Split the list into two halves using slow-fast pointers
    SingleLinkedListNode<int>* slow = head;
    SingleLinkedListNode<int>* fast = head;
    SingleLinkedListNode<int>* prev = nullptr;

    while (fast && fast->next) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    prev->next = nullptr;  // Split the list into two halves

    // Recursive sort on both halves
    SingleLinkedListNode<int>* left = mergeSortLinkedList(head);
    SingleLinkedListNode<int>* right = mergeSortLinkedList(slow);

    // Merge the sorted halves
    return mergeLinkedList(left, right);
}

// Main function to sort the linked list
void SortLinkedList::sortLinkedList2_4(SingleLinkedListNode<int>*& head) {
    if (!head) return;  // Empty list check
    head = mergeSortLinkedList(head);
}
