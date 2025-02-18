//
// Created by Zebin Guo on 1/6/25.
//
#include <algorithm>
#include <TreeNode.hpp>

class CheckBalancedSearchTree {
private:
    static int checkBSTHeight(const std::unique_ptr<BinaryTreeNode<int>>& root) {
        if (!root) return 0;
        int leftHeight = checkBSTHeight(root->left);
        if (leftHeight < 0) return -1;
        int rightHeight = checkBSTHeight(root->right);
        if (rightHeight < 0) return -1;
        if (std::abs(leftHeight - rightHeight) > 1) return -1;

        return std::max(leftHeight, rightHeight) + 1;
    }

    static bool isBSTTreeHelper(const std::unique_ptr<BinaryTreeNode<int>>& root, int minValue, int maxValue) {

    }

public:
    static bool isBalanced(const std::unique_ptr<BinaryTreeNode<int>>& root) {
        if (!root) return true;
        return  checkBSTHeight(root) != -1;
    }

    static bool isBSTTree(const std::unique_ptr<BinaryTreeNode<int>>& root) {
        // BST tree核心是 root->left < root < root->right
        if (!root) return true;
        return isBSTTreeHelper(root, INT_MIN, INT_MAX);
    }
};