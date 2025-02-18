#include <iostream>
#include "Vector.hpp"
#include "sort.hpp"
#include "String.hpp"
#include "SingleLinkedList.hpp"

#include "Headers/isCharacterUnique.hpp"
#include "Headers/areSimilarStrings.hpp"
#include "Headers/subStringReplacement.hpp"
#include "Headers/editDistance.hpp"
#include "Headers/stringCompression.hpp"
#include "Headers/removeDuplicateNode.hpp"
#include "Headers/removeKthNode.hpp"
#include "Headers/removeMiddleNode.hpp"
#include "Headers/sortLinkedList.hpp"
#include "Headers/LinkedListSum.hpp"
#include "palindromeLinkedList.hpp"
#include "Headers/connectLinkedList.hpp"
#include "Headers/loopNodeLinkedList.hpp"

#include "chap3/minStack.cpp"
#include "chap3/twoStackQueue.cpp"
#include "Chap4/FindDirectedGraphPath.cpp"
#include "Chap4/minHeightTree.cpp"
#include "Chap4/checkBalancedSearchTree.cpp"

void run_sort_tests();
void run_vector_tests();
void run_chap1_tests();
void run_chap2_tests();
void run_chap3_tests();
void run_chap4_tests();

int main(int argc, char *argv[]) {
    if (argc == 2 && std::string(argv[1]) == "--sort") {
        run_sort_tests();
    } else if (argc == 2 && std::string(argv[1]) == "--vector") {
        run_vector_tests();
    } else if (argc == 2 && std::string(argv[1]) == "--chap1") {
        run_chap1_tests();
    } else if (argc == 2 && std::string(argv[1]) == "--chap2") {
        run_chap2_tests();
    } else if (argc == 2 && std::string(argv[1]) == "--chap3") {
        run_chap3_tests();
    } else if (argc == 2 && std::string(argv[1]) == "--chap4") {
        run_chap4_tests();
    }


    else {
        std::cerr << "Usage: " << argv[0] << " --sort" << std::endl;
    }

    return 0;
}


void run_sort_tests() {
    Vector<int> vec = {5, 3, 8, 1, 2};
    Sort::bubbleSort(vec);
    std::cout << "Using bubbleSort" << std::endl;
    for (const auto& num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "Using selectionSort" << std::endl;
    Sort::selectionSort(vec);
    for (const auto& num : vec) {
        std::cout << num << " ";
    }
}

void run_vector_tests() {
    Vector<int> vec = {5, 3, 8, 1, 2};
    vec.push_back(3);
    vec.push_back(8);
    vec.push_back(2);
    for (const auto& num : vec) {
        std::cout << num << " ";
    }
}

void run_chap1_tests() {
    String s1("hello world");
    std::cout << "test s1 substring:" << s1.substr(2).data() << std::endl;
    std::cout << "test s1 find at index: " << s1.find("ll") << std::endl;
    std::cout << "Problem 1: " << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Input: " << s1.data() << " - " << "Output: " << isCharacterUnique::isCharacterUnique_1_1(s1) << std::endl;
    std::cout << "--------" << std::endl;
    String s2("helol wrdol");
    std::cout << "Problem 2: " << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Input1 After sorting: " << s1.data() << " - " << "Input2: " << s2.data() << " - " << "Output: " << areSimilarStrings::areSimilarStrings1_2(s1, s2) << std::endl;
    std::cout << "--------" << std::endl;
    String s3("What a beautiful world!");
    std::cout << "Problem 3: " << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Input: " << s3.data() << " - " << "Output: " << subStringReplacement::subStringReplacement_1_3(s3, " ", "%20").data() << std::endl;
    std::cout << "--------" << std::endl;
    String s4_1("Hello world!");
    String s4_2("Helo worldew!");
    std::cout << "Problem 4: " << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Input1: " << s4_1.data() << " - " << "Input2: " << s4_2.data() << " - " << "Output: " << editDistance::minDistance(s4_1, s4_2) << std::endl;
    std::cout << "--------" << std::endl;
    String s5_1("hhheeellloooooooo");
    String s5_2("helllo world");
    std::cout << "Problem 5: " << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Input1: " << s5_1.data() << " - " << "Output: " << stringCompression::stringCompression_1_6(s5_1).data() << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Input2: " << s5_2.data() << " - " << "Output: " << stringCompression::stringCompression_1_6(s5_2).data() << std::endl;
    std::cout << "--------" << std::endl;


}

void run_chap2_tests() {
    const Vector<int> vec = {5, 3, 8, 1, 2, 4, 6, 7};
    auto* list_2_1 = new SingleLinkedList<int>(vec);
    std::cout << "Problem 1: " << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Input: ";
    list_2_1->printLinkedList();
    std::cout << "Output: ";
    removeDuplicateNode::removeDuplicateNode_2_1(list_2_1->head);
    list_2_1->printLinkedList();

    std::cout << "--------" << std::endl;

    auto* list_2_2 = new SingleLinkedList<int>(vec);
    std::cout << "Problem 2: " << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Input1: ";
    list_2_2->printLinkedList();
    std::cout << "Output: ";
    RemoveKthNode::removeKthNode2_2(list_2_2->head, 6);
    list_2_2->printLinkedList();

    std::cout << "--------" << std::endl;
    auto* list_2_3 = new SingleLinkedList<int>(vec);
    std::cout << "Problem 3: " << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Input1: ";
    list_2_3->printLinkedList();
    std::cout << "Output: ";
    SingleLinkedListNode<int>* node = list_2_3->head;
    node = node->next->next->next;
    RemoveMiddleNode::RemoveMiddleNode2_3(node);
    list_2_3->printLinkedList();

    std::cout << "--------" << std::endl;

    auto* list_2_4 = new SingleLinkedList<int>(vec);
    std::cout << "Problem 4: " << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Input1: ";
    list_2_4->printLinkedList();
    std::cout << "Output: ";
    SortLinkedList::sortLinkedList2_4(list_2_4->head);
    list_2_4->printLinkedList();

    std::cout << "--------" << std::endl;
    auto* list_2_5 = new SingleLinkedList<int>(vec);
    std::cout << "Problem 5: " << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Input1: ";
    list_2_5->printLinkedList();
    std::cout << "Output: ";

    auto* l = LinkedListSum::LinkedListSum2_5(list_2_5->head, list_2_5->head);
    while (l) {
        if (l->next)
            std::cout << l->value << " -> ";
        else
            std::cout << l->value;
        l = l->next;
    }
    std::cout << std::endl;

    std::cout << "--------" << std::endl;
    std::cout << "Problem 6: " << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Input1: ";
    auto* list_2_6_1 = new SingleLinkedList<int>({1,2,3,2,1});
    list_2_6_1->printLinkedList();
    std::cout << "--------" << std::endl;
    std::cout << "Output: ";
    std::cout <<  PalindromeLinkedList::isPalindrome(list_2_6_1) << std::endl;
    auto* list_2_6_2 = new SingleLinkedList<int>({1,2,3,4,1});
    std::cout << "--------" << std::endl;
    std::cout << "Input2: ";
    list_2_6_2->printLinkedList();
    std::cout << "Output: ";
    std::cout << PalindromeLinkedList::isPalindrome(list_2_6_2) << std::endl;

    std::cout << "--------" << std::endl;

    std::cout << "Problem 7: " << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Input1: ";
    auto* list_2_7 = new SingleLinkedList<int>({1, 2, 3, 4});
    auto* head_1 = list_2_7->head;
    auto* list_2_7_1 = new SingleLinkedList<int>({6, 7});
    auto* head_2 = list_2_7_1->head;

    // Manually creating an intersection at node '3'
    SingleLinkedListNode<int>* intersect = head_1->next->next;  // Node with value '3'
    head_2->next->next = intersect;

    std::cout << "List 1: ";
    list_2_7->printLinkedList();
    std::cout << "List 2: ";
    list_2_7_1->printLinkedList();

    auto* result = ConnectLinkedList::connectLinkedList(head_1, head_2);
    std::cout << "Intersection Node Value: " << (result ? result->value : -1) << std::endl;

    std::cout << "--------" << std::endl;

    std::cout << "Problem 8: " << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Input1: ";
    auto* list_2_8 = new SingleLinkedList<int>({1, 2, 3, 4, 5, 6});
    auto* tail = list_2_8->head;
    while (tail->next) {
        tail = tail->next;
    }
    auto* intermediateNode = list_2_8->head->next->next;
    tail->next = intermediateNode;
    std::cout << "--------" << std::endl;
    // std::cout << "Input1: ";
    // list_2_7->printLinkedList();
    std::cout << "Output: ";
    node = LoopNodeLinkedList::LoopNodeLinkedList2_8(list_2_8->head);
    std::cout << "Loop Node Found: " << node->value << std::endl;




}

void run_chap3_tests() {
    std::cout << "Chapter 3 Tests" << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "Min Stack: " << std::endl;
    MinStack<int> minStack;
    minStack.push(3);
    minStack.push(2);
    minStack.push(1);
    minStack.push(4);
    minStack.push(-1);
    minStack.push(5);

    std::cout << minStack.minElement() << std::endl;
    std::cout << "--------" << std::endl;
    std::cout << "TwoStackQueue " << std::endl;
    TwoStackQueue<int> queue;

    std::cout << "Pushing elements: 10, 20, 30" << std::endl;
    queue.push(10);
    queue.push(20);
    queue.push(30);

    std::cout << "Front element: " << queue.front() << std::endl; // Output: 10
    std::cout << "Back element: " << queue.back() << std::endl;   // Output: 30
    std::cout << "Queue size: " << queue.size() << std::endl;     // Output: 3

    std::cout << "Popping an element..." << std::endl;
    queue.pop(); // Removes 10
    std::cout << "Front element after pop: " << queue.front() << std::endl; // Output: 20
    std::cout << "Queue size: " << queue.size() << std::endl;               // Output: 2

    std::cout << "Pushing element: 40" << std::endl;
    queue.push(40);

    std::cout << "Front element: " << queue.front() << std::endl; // Output: 20
    std::cout << "Back element: " << queue.back() << std::endl;   // Output: 40
    std::cout << "Queue size: " << queue.size() << std::endl;     // Output: 3

    std::cout << "Popping all elements..." << std::endl;
    while (!queue.empty()) {
        std::cout << "Front: " << queue.front() << std::endl;
        queue.pop();
    }

    std::cout << "Queue size after emptying: " << queue.size() << std::endl; // Output: 0
    std::cout << "Is queue empty? " << (queue.empty() ? "Yes" : "No") << std::endl;

    // Test popping or accessing front from an empty queue
    try {
        queue.pop();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

    try {
        std::cout << "Trying to access front: " << queue.front() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

}

void run_chap4_tests() {
    // Example graph represented as an adjacency list
    Vector<Vector<int>> graph = {
        {1, 2, 4},    // Node 0 -> 1, 2
        {2},       // Node 1 -> 2
        {0, 3},    // Node 2 -> 0, 3
        {},       // Node 3 -> None
        {}        // Node 4 -> None
    };

    int src = 0, dest = 4;

    for (int method = 1; method <= 2; ++method) {
        Vector<int> path = DirectedGraphPath::FindDirectedGraphPath(graph, src, dest, method);
        std::cout << "Method " << method << ": ";
        if (path.empty()) {
            std::cout << "No path found";
        } else {
            for (int node : path) std::cout << node << " ";
        }
        std::cout << std::endl;
    }

    const Vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    MinHeightTree::buildMinHeightBinaryTree(nums);

    // Create a balanced binary tree
    auto root = std::make_unique<BinaryTreeNode<int>>(1);
    root->left = std::make_unique<BinaryTreeNode<int>>(2);
    root->right = std::make_unique<BinaryTreeNode<int>>(3);
    root->left->left = std::make_unique<BinaryTreeNode<int>>(4);
    root->left->right = std::make_unique<BinaryTreeNode<int>>(5);
    root->right->left = std::make_unique<BinaryTreeNode<int>>(6);
    root->right->right = std::make_unique<BinaryTreeNode<int>>(7);

    std::cout << "Is the tree balanced? " << (CheckBalancedSearchTree::isBalanced(root) ? "Yes" : "No") << std::endl;

    // Create an unbalanced binary tree
    auto unbalancedRoot = std::make_unique<BinaryTreeNode<int>>(1);
    unbalancedRoot->left = std::make_unique<BinaryTreeNode<int>>(2);
    unbalancedRoot->left->left = std::make_unique<BinaryTreeNode<int>>(3);
    unbalancedRoot->left->left->left = std::make_unique<BinaryTreeNode<int>>(4);

    std::cout << "Is the tree balanced? " << (CheckBalancedSearchTree::isBalanced(unbalancedRoot) ? "Yes" : "No") << std::endl;
}

