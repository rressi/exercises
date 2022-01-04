#include "is_sub_tree.h"

#include <cassert>

#include "binary_tree_hash.h"


namespace tree::binary {
namespace {

bool isSubTree(const BinaryTreeNode *container, const BinaryTreeNode *contained,
               HashMemo *hashMemo) {
  if (container && contained) {
    auto containerHash = hashTree(*container, hashMemo);
    auto containedHash = hashTree(*contained, hashMemo);
    if (containerHash == containedHash &&
        isSubTree(container->left.get(), contained->left.get(), hashMemo) &&
        isSubTree(container->right.get(), contained->right.get(), hashMemo)) {
      return true;
    } else {
      return isSubTree(container->left.get(), contained, hashMemo) ||
             isSubTree(container->right.get(), contained, hashMemo);
    }
  } else if (container || contained) {
    return false;
  } else {
    return true;
  }
}

}  // namespace

bool isSubTree(const BinaryTreeNode &container,
               const BinaryTreeNode &contained) {
  auto hashMemo = HashMemo();
  return isSubTree(&container, &contained, &hashMemo);
}

}  // namespace tree::binary
