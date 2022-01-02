#pragma once

#include <functional>
#include <string>

#include "tree.pb.h"

namespace tree {

class Tree {
   public:
    explicit Tree(pb::Node root);
    auto root() const -> const pb::Node&;

    using Depth = std::size_t;
    using VisitCallback = std::function<bool(pb::Node* node, Depth depth)>;

    void visitBreathFirst(VisitCallback visitCallback);
    void visitDepthFirst(VisitCallback visitCallback);

    void visitPreOrder(VisitCallback visitCallback);
    void visitInOrder(VisitCallback visitCallback);
    void visitPostOrder(VisitCallback visitCallback);

   private:
    pb::Node root_;
};

inline Tree::Tree(pb::Node root) : root_(std::move(root)) {}
inline auto Tree::root() const -> const pb::Node& { return root_; }

}  // namespace tree
