#pragma once

#include <functional>
#include <optional>
#include <string>

#include "tree.pb.h"

namespace tree {

template <class T>
using Opt = std::optional<T>;

class Tree {
 public:
  Tree() = default;
  explicit Tree(pb::Node root);
  auto root() const -> const pb::Node&;

  using Depth = std::size_t;
  enum class VisitOrder {
    DEPTH_FIRST,
    BREATH_FIRST,
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
  };
  enum class VisitStatus { CONTINUE, FINISH };

  using UpdateCallback =
      std::function<VisitStatus(pb::Node* node, Depth depth)>;
  void update(const UpdateCallback& updateNodeCallback,
              VisitOrder visitOrder = VisitOrder::BREATH_FIRST);

  using VisitCallback =
      std::function<VisitStatus(const pb::Node& node, Depth depth)>;
  void visit(const VisitCallback& updateNodeCallback,
             VisitOrder visitOrder = VisitOrder::BREATH_FIRST) const;

 private:
  pb::Node root_;
};

auto createBinaryTree(const std::vector<pb::Value>& inputValues,
                      Tree::VisitOrder visitOrder = Tree::VisitOrder::IN_ORDER)
    -> Opt<Tree>;

inline Tree::Tree(pb::Node root) : root_(std::move(root)) {}
inline auto Tree::root() const -> const pb::Node& { return root_; }

}  // namespace tree
