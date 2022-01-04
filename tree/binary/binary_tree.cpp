#include "binary_tree.h"

#include <cassert>


namespace tree::binary {

auto createBinaryTreeNode(std::string value) -> Ptr<BinaryTreeNode> {
  auto newNode = std::make_unique<BinaryTreeNode>();
  newNode->value = std::move(value);
  return newNode;
}

auto createBinaryTree(const std::vector<std::string> &values)
    -> Ptr<BinaryTreeNode> {
  return createBinaryTree(values.begin(), values.end());
}

auto createBinaryTree(std::vector<std::string>::const_iterator begin,
                      std::vector<std::string>::const_iterator end)
    -> Ptr<BinaryTreeNode> {
  if (begin >= end) {
    return {};
  }

  auto itPivot = begin + std::distance(begin, end) / 2;
  auto root = createBinaryTreeNode(*itPivot);

  root->left = createBinaryTree(begin, itPivot);
  root->right = createBinaryTree(itPivot + 1, end);

  return root;
}

bool isBinarySearchTree(const Ptr<BinaryTreeNode> &tree,
                        const Opt<std::string> &minValue,
                        const Opt<std::string> &maxValue) {
  if (tree) {
    if (minValue && tree->value < minValue) {
      return false;
    } else if (maxValue && tree->value > maxValue) {
      return false;
    } else {
      return isBinarySearchTree(tree->left, minValue, tree->value) &&
             isBinarySearchTree(tree->right, tree->value, maxValue);
    }
  } else {
    return true;
  }
}

}  // namespace tree::binary
