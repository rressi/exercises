#pragma once

#include <functional>

#include "binary_tree.h"


namespace tree::binary {

using Depth = std::size_t;

enum class VisitEvent { PRE_ORDER, IN_ORDER, POST_ORDER };
auto toString(const VisitEvent &visitEvent) -> std::string;

enum class VisitStatus { CONTINUE, FINISH, ABORT };
class VisitContext;

using VisitCallback =
    std::function<VisitStatus(const VisitContext &visitContext)>;

class VisitContext {
 public:
  VisitContext(const BinaryTreeNode &node, const VisitCallback &callback)
      : node_(&node), callback_(&callback) {}

  auto visit() -> VisitStatus;

  auto event() const -> VisitEvent { return event_; }
  auto depth() const -> Depth { return depth_; }
  auto node() const -> const BinaryTreeNode & { return *node_; }

 private:
  VisitEvent event_{};
  const BinaryTreeNode *node_{};
  Depth depth_{};
  const VisitCallback *callback_{};

  auto visitChild(const BinaryTreeNode *childNode) -> VisitStatus;
};

auto visit(const BinaryTreeNode &node, const VisitCallback &callback)
    -> VisitStatus;

}  // namespace tree::binary
