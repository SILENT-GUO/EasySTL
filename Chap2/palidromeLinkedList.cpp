#include "palindromeLinkedList.hpp"

bool PalindromeLinkedList::isPalindrome(const SingleLinkedList<int> *list) {
    if (!list || !list->head || !list->head->next) return true;  // Empty or single-node list is a palindrome

    SingleLinkedListNode<int>* head = list->head;

    // Step 1: Find the middle of the list using fast and slow pointers
    SingleLinkedListNode<int>* slow = head;
    SingleLinkedListNode<int>* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Step 2: Reverse the second half of the list
    SingleLinkedListNode<int>* prev = nullptr;
    SingleLinkedListNode<int>* current = slow;
    while (current) {
        SingleLinkedListNode<int>* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    SingleLinkedListNode<int>* reversedSecondHalf = prev;

    // Step 3: Compare the first half and reversed second half
    SingleLinkedListNode<int>* firstHalf = head;
    SingleLinkedListNode<int>* secondHalf = reversedSecondHalf;
    bool isPalindrome = true;
    while (secondHalf) {
        if (firstHalf->value != secondHalf->value) {
            isPalindrome = false;
            break;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }

    // Step 4: Restore the reversed second half (optional)
    prev = nullptr;
    current = reversedSecondHalf;
    while (current) {
        SingleLinkedListNode<int>* next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return isPalindrome;
}
