#pragma once

#include <memory>
#include <vector>

namespace binary_tree {

template<class T>
using Ptr = std::unique_ptr<T>;

struct BinaryTreeNode {
    std::string value{};
    Ptr<BinaryTreeNode> left{};
    Ptr<BinaryTreeNode> right{};
};

auto createBinaryTreeNode(std::string value) -> Ptr<BinaryTreeNode>;

auto createBinaryTree(const std::vector<std::string> &values) -> Ptr<BinaryTreeNode>;

auto createBinaryTree(std::vector<std::string>::const_iterator begin,
                      std::vector<std::string>::const_iterator end) -> Ptr<BinaryTreeNode>;

bool isSubTree(const Ptr<BinaryTreeNode> &container, const Ptr<BinaryTreeNode> &contained);
bool isSubTree(const BinaryTreeNode *container, BinaryTreeNode *contained);

} // namespace binary_tree

