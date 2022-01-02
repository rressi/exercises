#include "tree.h"

#include <queue>
#include <stack>
#include <stdexcept>

namespace tree {
namespace {

using Depth = Tree::Depth;
using Node = pb::Node;
using VisitStatus = Tree::VisitStatus;
using VisitCallback = Tree::VisitCallback;

void visitBreathFirst(const Node& node, Depth startDepth,
                      const VisitCallback& visitCallback) {
    using Task = std::tuple<const Node*, Depth>;
    auto queue = std::queue<Task>();
    queue.emplace(&node, startDepth);

    while (!queue.empty()) {
        auto [node, depth] = queue.front();
        queue.pop();

        auto status = visitCallback(*node, depth);
        if (status != VisitStatus::CONTINUE) return;

        for (const auto& child : node->children()) {
            queue.emplace(&child, depth + 1);
        }
    }
}

void visitDepthFirst(const Node& node, Depth startDepth,
                     const VisitCallback& visitCallback) {
    using Task = std::tuple<const Node*, Depth>;
    auto stack = std::stack<Task>();
    stack.emplace(&node, startDepth);

    while (!stack.empty()) {
        auto [node, depth] = stack.top();
        stack.pop();

        auto status = visitCallback(*node, depth);
        if (status != Tree::VisitStatus::CONTINUE) return;

        auto childrenStart = node->children().rbegin();
        auto childrenEnd = node->children().rend();
        for (auto it = childrenStart; it != childrenEnd; it++) {
            const auto& child = *it;
            stack.emplace(&child, depth + 1);
        }
    }
}

auto getLeft(const Node& node) -> const Node* {
    constexpr auto INDEX_OF_LEFT_NODE = 0;

    if (node.children_size() > INDEX_OF_LEFT_NODE) {
        const auto& child = node.children().at(INDEX_OF_LEFT_NODE);
        return &child;
    }

    return nullptr;
}

auto getRight(const Node& node) -> const Node* {
    constexpr auto INDEX_OF_RIGHT_NODE = 1;

    if (node.children_size() > INDEX_OF_RIGHT_NODE) {
        auto& child = node.children().at(INDEX_OF_RIGHT_NODE);
        return &child;
    }

    return nullptr;
}

auto visitPreOrder(const Node& node, Depth depth,
                   const VisitCallback& visitCallback) -> VisitStatus {
    if (node.children_size() > 2) {
        throw std::runtime_error(
            "In order scan have sense onlyt on binary trees");
    }

    auto status = visitCallback(node, depth);
    if (status != VisitStatus::CONTINUE) return status;

    if (auto child = getLeft(node)) {
        auto status = visitPreOrder(*child, depth + 1, visitCallback);
        if (status != VisitStatus::CONTINUE) {
            return status;
        }
    }

    if (auto child = getRight(node)) {
        auto status = visitPreOrder(*child, depth + 1, visitCallback);
        if (status != VisitStatus::CONTINUE) {
            return status;
        }
    }

    return VisitStatus::CONTINUE;
}

auto visitInOrder(const Node& node, Depth depth,
                  const VisitCallback& visitCallback) -> Tree::VisitStatus {
    if (node.children_size() > 2) {
        throw std::runtime_error(
            "In order scan have sense onlyt on binary trees");
    }

    if (auto child = getLeft(node)) {
        auto status = visitInOrder(*child, depth + 1, visitCallback);
        if (status != VisitStatus::CONTINUE) {
            return status;
        }
    }

    auto status = visitCallback(node, depth);
    if (status != VisitStatus::CONTINUE) return status;

    if (auto child = getRight(node)) {
        auto status = visitInOrder(*child, depth + 1, visitCallback);
        if (status != VisitStatus::CONTINUE) {
            return status;
        }
    }

    return VisitStatus::CONTINUE;
}

auto visitPostOrder(const Node& node, Depth depth,
                    const VisitCallback& visitCallback) -> VisitStatus {
    if (node.children_size() > 2) {
        throw std::runtime_error(
            "In order scan have sense onlyt on binary trees");
    }

    if (auto child = getLeft(node)) {
        auto status = visitPostOrder(*child, depth + 1, visitCallback);
        if (status != VisitStatus::CONTINUE) {
            return status;
        }
    }

    if (auto child = getRight(node)) {
        auto status = visitPostOrder(*child, depth + 1, visitCallback);
        if (status != VisitStatus::CONTINUE) {
            return status;
        }
    }

    auto status = visitCallback(node, depth);
    if (status != VisitStatus::CONTINUE) return status;

    return VisitStatus::CONTINUE;
}

}  // namespace

void Tree::visit(const VisitCallback& visitCallback,
                 VisitOrder visitOrder) const {
    constexpr auto ZERO_DEPTH = Depth();

    switch (visitOrder) {
        case VisitOrder::DEPTH_FIRST:
            tree::visitDepthFirst(root_, ZERO_DEPTH, visitCallback);
            break;
        case VisitOrder::BREATH_FIRST:
            tree::visitBreathFirst(root_, ZERO_DEPTH, visitCallback);
            break;
        case VisitOrder::PRE_ORDER:
            tree::visitPreOrder(root_, ZERO_DEPTH, visitCallback);
            break;
        case VisitOrder::IN_ORDER:
            tree::visitInOrder(root_, ZERO_DEPTH, visitCallback);
            break;
        case VisitOrder::POST_ORDER:
            tree::visitPostOrder(root_, ZERO_DEPTH, visitCallback);
            break;
    }
}

void Tree::update(const UpdateCallback& updateCallback, VisitOrder visitOrder) {
    auto onVisitNode = [&updateCallback](const pb::Node& node, Depth depth) {
        return updateCallback(const_cast<pb::Node*>(&node), depth);
    };
    visit(onVisitNode, visitOrder);
}

namespace {

template <class N>
auto discreteSquareRoot(N x) -> N {
    auto y = N();
    while (x) {
        y++;
        x /= 2;
    }
    return y;
}

}  // namespace

auto createBinaryTree(const std::vector<pb::Value>& inputValues,
                      Tree::VisitOrder visitOrder) -> Opt<Tree> {
    using Depth = Tree::Depth;

    if (inputValues.empty()) {
        return {};
    }

    auto tree = Tree();

    auto maxDepth = discreteSquareRoot<Depth>(inputValues.size()) - 1;
    auto onCreateNode = [maxDepth](pb::Node* node, Depth depth) {
        if (depth < maxDepth) {
            node->add_children();
            node->add_children();
        }
        return VisitStatus::CONTINUE;
    };
    tree.update(onCreateNode, Tree::VisitOrder::BREATH_FIRST);

    auto nextNodeIndex = std::size_t(0);
    auto onVisitNode = [&](pb::Node* node, Depth depth) {
        auto nevValue = node->mutable_value();
        (*nevValue) = inputValues[nextNodeIndex];
        nextNodeIndex++;

        auto hasFinished = bool(nextNodeIndex == inputValues.size());
        return hasFinished ? VisitStatus::FINISH  //
                           : VisitStatus::CONTINUE;
    };
    tree.update(onVisitNode, visitOrder);

    return tree;
}

}  // namespace tree
