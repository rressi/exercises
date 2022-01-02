#pragma once

#include <functional>
#include <string>

#include "tree.pb.h"

namespace tree {

class Tree {
   public:
    Tree() = default;
    explicit Tree(pb::Node root);
    auto root() const -> const pb::Node&;

    using Depth = std::size_t;
    using VisitCallback = std::function<bool(pb::Node* node, Depth depth)>;

    enum class VisitOrder {
        DEPTH_FIRST,
        BREATH_FIRST,
        PRE_ORDER,
        IN_ORDER,
        POST_ORDER
    };

    void visit(VisitCallback visitCallback,
               Tree::VisitOrder visitOrder = Tree::VisitOrder::DEPTH_FIRST);

   private:
    pb::Node root_;
};

auto createBinaryTree(const std::vector<pb::Value>& inputValues,
                      Tree::VisitOrder visitOrder = Tree::VisitOrder::IN_ORDER)
    -> Tree;

inline Tree::Tree(pb::Node root) : root_(std::move(root)) {}
inline auto Tree::root() const -> const pb::Node& { return root_; }

}  // namespace tree
