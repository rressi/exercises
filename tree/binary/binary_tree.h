#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace tree::binary {

template <class T>
using Ptr = std::unique_ptr<T>;

template <class T>
using Opt = std::optional<T>;

struct BinaryTreeNode {
  std::string value{};
  Ptr<BinaryTreeNode> left{};
  Ptr<BinaryTreeNode> right{};
};

auto createBinaryTreeNode(std::string value) -> Ptr<BinaryTreeNode>;

auto createBinaryTree(const std::vector<std::string> &values)
    -> Ptr<BinaryTreeNode>;

auto createBinaryTree(std::vector<std::string>::const_iterator begin,
                      std::vector<std::string>::const_iterator end)
    -> Ptr<BinaryTreeNode>;

bool isSubTree(const Ptr<BinaryTreeNode> &container,
               const Ptr<BinaryTreeNode> &contained);
bool isSubTree(const BinaryTreeNode *container,
               const BinaryTreeNode *contained);

bool isBinarySearchTree(const Ptr<BinaryTreeNode> &tree,
                        const Opt<std::string> &minValue = {},
                        const Opt<std::string> &maxValue = {});

}  // namespace tree::binary
