#include "binary_tree_visit.h"

#include <stdexcept>

namespace tree::binary {

auto toString(const VisitEvent &visitEvent) -> std::string {
  switch (visitEvent) {
    case VisitEvent::PRE_ORDER:
      return "PRE_ORDER";
    case VisitEvent::IN_ORDER:
      return "IN_ORDER";
    case VisitEvent::POST_ORDER:
      return "POST_ORDER";
    default:
      throw std::runtime_error("Invalid VisitEvent: " +
                               std::to_string(int(visitEvent)));
  }
}

auto VisitContext::visit() -> VisitStatus {
  event_ = VisitEvent::PRE_ORDER;
  auto status = (*callback_)(*this);
  if (status != VisitStatus::CONTINUE) return status;

  status = visitChild(node_->left.get());
  if (status != VisitStatus::CONTINUE) return status;

  event_ = VisitEvent::IN_ORDER;
  status = (*callback_)(*this);
  if (status != VisitStatus::CONTINUE) return status;

  status = visitChild(node_->right.get());
  if (status != VisitStatus::CONTINUE) return status;

  event_ = VisitEvent::POST_ORDER;
  status = (*callback_)(*this);

  return status;
}

auto VisitContext::visitChild(const BinaryTreeNode *childNode) -> VisitStatus {
  auto status = VisitStatus::CONTINUE;

  if (childNode) {
    auto originalNode = node_;
    auto originalDepth = depth_;

    node_ = childNode;
    depth_++;

    try {
      status = visit();
    } catch (...) {
      depth_ = originalDepth;
      node_ = originalNode;
      throw;
    }

    depth_ = originalDepth;
    node_ = originalNode;
  }

  return status;
}

auto visit(const BinaryTreeNode &root, const VisitCallback &visitCallback)
    -> VisitStatus {
  return VisitContext(root, visitCallback).visit();
}

}  // namespace tree::binary
