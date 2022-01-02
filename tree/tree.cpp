#include "tree.h"

#include <queue>
#include <stack>
#include <stdexcept>

namespace tree {
namespace {

void visitBreathFirst(pb::Node* node, Tree::Depth depth,
                      Tree::VisitCallback visitCallback) {
    using Task = std::tuple<pb::Node*, Tree::Depth>;
    auto queue = std::queue<Task>();
    queue.emplace(node, depth);

    while (!queue.empty()) {
        auto [node, depth] = queue.front();
        queue.pop();

        auto continueLoop = visitCallback(node, depth);
        if (!continueLoop) return;

        if (auto numChildren = node->children_size()) {
            auto children = node->mutable_children();
            for (auto& child : *children) {
                if (child.has_value()) {
                    queue.emplace(&child, depth + 1);
                }
            }
        }
    }
}

void visitDepthFirst(pb::Node* node, Tree::Depth depth,
                     Tree::VisitCallback visitCallback) {
    using Task = std::tuple<pb::Node*, Tree::Depth>;
    auto stack = std::stack<Task>();
    stack.emplace(node, depth);

    while (!stack.empty()) {
        auto [node, depth] = stack.top();
        stack.pop();

        auto continueLoop = visitCallback(node, depth);
        if (!continueLoop) return;

        if (auto numChildren = node->children_size()) {
            auto children = node->mutable_children();
            for (auto& child : *children) {
                if (child.has_value()) {
                    stack.emplace(&child, depth + 1);
                }
            }
        }
    }
}

auto getLeftChild(pb::Node* node) -> pb::Node* {
    constexpr auto INDEX_OF_LEFT_NODE = 1;

    if (node && node->children_size() >= INDEX_OF_LEFT_NODE) {
        auto& child = node->mutable_children()->at(INDEX_OF_LEFT_NODE);
        if (child.has_value()) {
            return &child;
        }
    }
    return nullptr;
}

auto getRightChild(pb::Node* node) -> pb::Node* {
    constexpr auto INDEX_OF_RIGHT_NODE = 2;

    if (node && node->children_size() >= INDEX_OF_RIGHT_NODE) {
        auto& child = node->mutable_children()->at(INDEX_OF_RIGHT_NODE);
        if (child.has_value()) {
            return &child;
        }
    }
    return nullptr;
}

bool visitPreOrder(pb::Node* node, Tree::Depth depth,
                   Tree::VisitCallback visitCallback) {
    if (node->children_size() > 2) {
        throw std::runtime_error(
            "In order scan have sense onlyt on binary trees");
    }

    if (!visitCallback(node, depth)) {
        return false;
    }

    if (auto child = getLeftChild(node)) {
        if (!visitPreOrder(child, depth + 1, visitCallback)) {
            return false;
        }
    }

    if (auto child = getRightChild(node)) {
        if (!visitPreOrder(child, depth + 1, visitCallback)) {
            return false;
        }
    }

    return true;
}

bool visitInOrder(pb::Node* node, Tree::Depth depth,
                  Tree::VisitCallback visitCallback) {
    if (node->children_size() > 2) {
        throw std::runtime_error(
            "In order scan have sense onlyt on binary trees");
    }

    if (auto child = getLeftChild(node)) {
        if (!visitInOrder(child, depth + 1, visitCallback)) {
            return false;
        }
    }

    if (!visitCallback(node, depth)) {
        return false;
    }

    if (auto child = getRightChild(node)) {
        if (!visitInOrder(child, depth + 1, visitCallback)) {
            return false;
        }
    }

    return true;
}

bool visitPostOrder(pb::Node* node, Tree::Depth depth,
                    Tree::VisitCallback visitCallback) {
    if (node->children_size() > 2) {
        throw std::runtime_error(
            "In order scan have sense onlyt on binary trees");
    }

    if (auto child = getLeftChild(node)) {
        if (!visitPostOrder(child, depth + 1, visitCallback)) {
            return false;
        }
    }

    if (auto child = getRightChild(node)) {
        if (!visitPostOrder(child, depth + 1, visitCallback)) {
            return false;
        }
    }

    if (!visitCallback(node, depth)) {
        return false;
    }

    return true;
}

}  // namespace

void Tree::visitBreathFirst(VisitCallback visitCallback) {
    tree::visitBreathFirst(&root_, 0, visitCallback);
}

void Tree::visitDepthFirst(VisitCallback visitCallback) {
    tree::visitDepthFirst(&root_, 0, visitCallback);
}

void Tree::visitPreOrder(VisitCallback visitCallback) {
    tree::visitPreOrder(&root_, 0, visitCallback);
}

void Tree::visitInOrder(VisitCallback visitCallback) {
    tree::visitInOrder(&root_, 0, visitCallback);
}

void Tree::visitPostOrder(VisitCallback visitCallback) {
    tree::visitPostOrder(&root_, 0, visitCallback);
}

}  // namespace tree
