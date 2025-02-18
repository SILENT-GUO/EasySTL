//
// Created by Zebin Guo on 1/5/25.
//

#ifndef TREENODE_HPP
#define TREENODE_HPP
#include <memory>

template <typename T>
class BinaryTreeNode {
public:
    T data;
    std::unique_ptr<BinaryTreeNode<T>> left;
    std::unique_ptr<BinaryTreeNode<T>> right;
    explicit BinaryTreeNode(const T& value): data(value), left(nullptr), right(nullptr) {}
};

#endif //TREENODE_HPP
