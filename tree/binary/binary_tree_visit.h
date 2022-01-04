#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "binary_tree.h"

namespace tree::binary {

enum class VisitEvent { ENTER, EXIT };
using Depth = std::size_t;
struct VisitContext {
  VisitEvent visitEvent{};
  const BinaryTreeNode *node{};
  Depth depth;
};

enum class VisitStatus { CONTINUE, FINISH, ABORT };
using VisitCallback =
    std::function<VisitStatus(const VisitContext &visitContext)>;

auto visit(const Ptr<BinaryTreeNode> &root, const VisitCallback &visitCallback)
    -> VisitStatus;
auto visit(const BinaryTreeNode *root, const VisitCallback &visitCallback)
    -> VisitStatus;

}  // namespace tree::binary
