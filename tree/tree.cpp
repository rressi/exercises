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

auto getLeft(pb::Node* node) -> pb::Node* {
    constexpr auto INDEX_OF_LEFT_NODE = 0;

    if (node && node->children_size() >= INDEX_OF_LEFT_NODE) {
        auto& child = node->mutable_children()->at(INDEX_OF_LEFT_NODE);
        if (child.has_value()) {
            return &child;
        }
    }
    return nullptr;
}

auto getRight(pb::Node* node) -> pb::Node* {
    constexpr auto INDEX_OF_RIGHT_NODE = 1;

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

    if (auto child = getLeft(node)) {
        if (!visitPreOrder(child, depth + 1, visitCallback)) {
            return false;
        }
    }

    if (auto child = getRight(node)) {
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

    if (auto child = getLeft(node)) {
        if (!visitInOrder(child, depth + 1, visitCallback)) {
            return false;
        }
    }

    if (!visitCallback(node, depth)) {
        return false;
    }

    if (auto child = getRight(node)) {
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

    if (auto child = getLeft(node)) {
        if (!visitPostOrder(child, depth + 1, visitCallback)) {
            return false;
        }
    }

    if (auto child = getRight(node)) {
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

void Tree::visit(VisitCallback visitCallback, VisitOrder visitOrder) {
    switch (visitOrder) {
        case VisitOrder::DEPTH_FIRST:
            tree::visitDepthFirst(&root_, 0, visitCallback);
            break;
        case VisitOrder::BREATH_FIRST:
            tree::visitBreathFirst(&root_, 0, visitCallback);
            break;
        case VisitOrder::PRE_ORDER:
            tree::visitPreOrder(&root_, 0, visitCallback);
            break;
        case VisitOrder::IN_ORDER:
            tree::visitInOrder(&root_, 0, visitCallback);
            break;
        case VisitOrder::POST_ORDER:
            tree::visitPostOrder(&root_, 0, visitCallback);
            break;
    }
}

// namespace {

// auto mutableLeft(pb::Node* node, const pb::Value& defaultValue) -> pb::Node*
// {
//     constexpr auto INDEX_OF_LEFT_NODE = 0;

//     if (!node) return nullptr;

//     if (node->children_size() <= INDEX_OF_LEFT_NODE) {
//         auto newChild = node->add_children();
//         auto newValue = newChild->mutable_value();
//         (*newValue) = defaultValue;
//         return newChild;
//     }

//     auto& child = node->mutable_children()->at(INDEX_OF_LEFT_NODE);
//     return &child;
// }

// auto mutableRight(pb::Node* node, const pb::Value& defaultValue) -> pb::Node*
// {
//     constexpr auto INDEX_OF_LEFT_NODE = 0;
//     constexpr auto INDEX_OF_RIGHT_NODE = 1;

//     if (!node) return nullptr;

//     if (node->children_size() <= INDEX_OF_LEFT_NODE) {
//         auto newChild = node->add_children();
//     }

//     if (node->children_size() <= INDEX_OF_RIGHT_NODE) {
//         auto newChild = node->add_children();
//         auto newValue = newChild->mutable_value();
//         (*newValue) = defaultValue;
//         return newChild;
//     }

//     auto& child = node->mutable_children()->at(INDEX_OF_RIGHT_NODE);
//     return &child;
// }

// }  // namespace

auto createBinaryTree(const std::vector<pb::Value>& inputValues,
                      Tree::VisitOrder visitOrder) -> Tree {
    auto nextNodeIndex = std::size_t(0);
    auto onNewNode = [&](pb::Node* node, Tree::Depth) {
        auto nevValue = node->mutable_value();

        (*nevValue) = inputValues[nextNodeIndex];
        nextNodeIndex++;
        if (nextNodeIndex == inputValues.size()) {
            return false;
        }

        node->add_children();
        node->add_children();
        return true;
    };

    auto tree = Tree();
    tree.visit(onNewNode, visitOrder);
    return tree;
}

}  // namespace tree
