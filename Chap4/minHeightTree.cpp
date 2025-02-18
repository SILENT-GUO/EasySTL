//
// Created by Zebin Guo on 1/5/25.
//

// 给定一个有序的整数数组，创建一个最小高度的二叉搜索树

#include <iostream>
#include <TreeNode.hpp>
#include <Vector.hpp>


class MinHeightTree {
private:
    static void preOrderTraversal(const std::unique_ptr<BinaryTreeNode<int>>& root) {
        if (!root) return;
        std::cout << root->data << " ";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
    static void inOrderTraversal(const std::unique_ptr<BinaryTreeNode<int>>& root) {
        if (!root) return;
        inOrderTraversal(root->left);
        std::cout << root->data << " ";
        inOrderTraversal(root->right);
    }
    static void postOrderTraversal(const std::unique_ptr<BinaryTreeNode<int>>& root) {
        if (!root) return;
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        std::cout << root->data << " ";
    }
public:
    static std::unique_ptr<BinaryTreeNode<int>> buildMinHeightBinaryTreeHelper(const Vector<int>& v, int left, int right) {
        if (left > right) return nullptr;
        const int mid = left + (right - left) / 2;
        auto midTreeNode = std::make_unique<BinaryTreeNode<int>>(v[mid]);
        midTreeNode->left = buildMinHeightBinaryTreeHelper(v, left, mid-1);
        midTreeNode->right = buildMinHeightBinaryTreeHelper(v, mid+1, right);
        return midTreeNode;
    }
    static void buildMinHeightBinaryTree(const Vector<int>& v) {
        std::unique_ptr<BinaryTreeNode<int>> root = buildMinHeightBinaryTreeHelper(v, 0, v.size() - 1);
        preOrderTraversal(root);
    }
};
