cmake_minimum_required(VERSION 3.30)
project(CC189)

set(CMAKE_CXX_STANDARD 17)

add_executable(CC189 main.cpp Chap1/isCharacterUnique.cpp
        Chap1/areSimilarStrings.cpp
        Chap1/subStringReplacement.cpp
        Chap1/editDistance.cpp
        Headers/editDistance.hpp
        Chap1/stringCompression.cpp
        Headers/stringCompression.hpp
        Chap1/MatrixRotation.cpp
        Headers/MatrixRotation.hpp
        Container/SingleLinkedList.hpp
        Chap2/removeDuplicateNode.cpp
        Headers/removeDuplicateNode.hpp
        Chap2/removeKthNode.cpp
        Headers/removeKthNode.hpp
        Chap2/removeMiddleNode.cpp
        Headers/removeMiddleNode.hpp
        Chap2/sortLinkedList.cpp
        Headers/sortLinkedList.hpp
        Chap2/LinkedListSUm.cpp
        Headers/LinkedListSum.hpp
        Chap2/connectLinkedList.cpp
        Headers/connectLinkedList.hpp
        Chap2/loopNodeLinkedList.cpp
        Headers/loopNodeLinkedList.hpp
        Chap2/palidromeLinkedList.cpp
        Headers/palindromeLinkedList.hpp
        Container/Stack.hpp
        Container/Queue.hpp
        chap3/minStack.cpp
        chap3/twoStackQueue.cpp
        chap3/SortedStack.cpp
        Container/TreeNode.hpp
        Chap4/FindDirectedGraphPath.cpp
        Chap4/minHeightTree.cpp
        Chap4/checkBalancedSearchTree.cpp
)

target_include_directories(CC189 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Container
        ${CMAKE_CURRENT_SOURCE_DIR}/Utils
        ${CMAKE_CURRENT_SOURCE_DIR}/Headers
)
