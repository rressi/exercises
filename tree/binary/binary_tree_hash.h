#pragma once

#include <unordered_map>

#include "binary_tree.h"

namespace tree::binary {

using HashCode = std::uint32_t;

class HashMemo {
 public:
  auto hashNode(const BinaryTreeNode& node) -> HashCode;

  auto operator()(const BinaryTreeNode& node) -> HashCode {
    return hashNode(node);
  }

 private:
  std::unordered_map<const BinaryTreeNode*, HashCode> cachedResults_{};
};

auto hashTree(const BinaryTreeNode& root, HashMemo* hashMemo = nullptr)
    -> HashCode;

constexpr auto HASH_NODE_SEED = HashCode(181);
constexpr auto HASH_NODE_COMBINE_FACTOR_LEFT = HashCode(197);
constexpr auto HASH_NODE_COMBINE_FACTOR_RIGHT = HashCode(211);

}  // namespace tree::binary
