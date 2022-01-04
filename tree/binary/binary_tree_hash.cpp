#include "binary_tree_hash.h"

#include <zlib/zlib.h>


namespace tree::binary {

auto HashMemo::hashNode(const BinaryTreeNode& node) -> HashCode {
  auto cachedIt = cachedResults_.find(&node);
  if (cachedIt != cachedResults_.end()) {
    return cachedIt->second;
  }

  auto newHash =
      ::crc32(HASH_NODE_SEED, reinterpret_cast<const Bytef*>(node.value.data()),
              node.value.size());

  if (node.left) {
    auto leftHash = hashNode(*node.left);
    newHash ^= leftHash * HASH_NODE_COMBINE_FACTOR_LEFT;
  }

  if (node.right) {
    auto rightHash = hashNode(*node.right);
    newHash ^= rightHash * HASH_NODE_COMBINE_FACTOR_RIGHT;
  }

  cachedResults_.emplace(&node, newHash);

  return newHash;
}

auto hashTree(const BinaryTreeNode& root, HashMemo* hashMemo) -> HashCode {
  if (hashMemo) {
    return hashMemo->hashNode(root);
  } else {
    return HashMemo().hashNode(root);
  }
}

}  // namespace tree::binary
