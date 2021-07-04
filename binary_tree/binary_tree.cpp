#include "binary_tree.h"

#include <cassert>

namespace binary_tree {

auto createBinaryTreeNode(std::string value) -> Ptr<BinaryTreeNode> {
    auto newNode = std::make_unique<BinaryTreeNode>();
    newNode->value = std::move(value);
    return newNode;
}

auto createBinaryTree(const std::vector<std::string> &values) -> Ptr<BinaryTreeNode> {
    return createBinaryTree(values.begin(), values.end());
}

auto createBinaryTree(std::vector<std::string>::const_iterator begin,
                      std::vector<std::string>::const_iterator end) -> Ptr<BinaryTreeNode> {

    if (begin >= end) {
        return {};
    }

    auto itPivot = begin + std::distance(begin, end) / 2;
    auto root = createBinaryTreeNode(*itPivot);

    root->left = createBinaryTree(begin, itPivot);
    root->right = createBinaryTree(itPivot + 1, end);

    return root;
}


} // namespace binary_tree
