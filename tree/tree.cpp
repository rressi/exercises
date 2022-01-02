#include "tree.h"

#include <queue>
#include <stdexcept>

namespace tree {
namespace {

void visitDepthFirst(pb::Node* node, Tree::Depth depth,
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
                queue.emplace(&child, depth + 1);
            }
        }
    }
}

bool visitPreOrder(pb::Node* node, Tree::Depth depth,
                   Tree::VisitCallback visitCallback) {
    auto continueLoop = true;
    switch (node->children_size()) {
        case 0:
            continueLoop = visitCallback(node, depth);
            break;

        case 1: {
            auto& leftChild = node->mutable_children()->at(0);

            continueLoop = visitCallback(node, depth) &&
                           visitPreOrder(&leftChild, depth + 1, visitCallback);
            break;
        }

        case 2: {
            auto& leftChild = node->mutable_children()->at(0);
            auto& rightChild = node->mutable_children()->at(1);

            continueLoop =
                visitCallback(node, depth) &&
                visitPreOrder(&leftChild, depth + 1, visitCallback) &&
                visitPreOrder(&rightChild, depth + 1, visitCallback);
            break;
        }

        default:
            throw std::runtime_error(
                "In order scan have sense onlyt on binary trees");
    }

    return continueLoop;
}

bool visitInOrder(pb::Node* node, Tree::Depth depth,
                  Tree::VisitCallback visitCallback) {
    auto continueLoop = true;
    switch (node->children_size()) {
        case 0:
            continueLoop = visitCallback(node, depth);
            break;

        case 1: {
            auto& leftChild = node->mutable_children()->at(0);

            continueLoop = visitInOrder(&leftChild, depth + 1, visitCallback) &&
                           visitCallback(node, depth);
            break;
        }

        case 2: {
            auto& leftChild = node->mutable_children()->at(0);
            auto& rightChild = node->mutable_children()->at(1);
            continueLoop = visitInOrder(&leftChild, depth + 1, visitCallback) &&
                           visitCallback(node, depth) &&
                           visitInOrder(&rightChild, depth + 1, visitCallback);
            break;
        }

        default:
            throw std::runtime_error(
                "In order scan have sense onlyt on binary trees");
    }
    return continueLoop;
}

bool visitPostOrder(pb::Node* node, Tree::Depth depth,
                    Tree::VisitCallback visitCallback) {
    auto continueLoop = true;
    switch (node->children_size()) {
        case 0:
            continueLoop = visitCallback(node, depth);
            break;

        case 1: {
            auto& leftChild = node->mutable_children()->at(0);

            continueLoop = visitCallback(&leftChild, depth + 1) &&
                           visitCallback(node, depth);
            break;
        }

        case 2: {
            auto& leftChild = node->mutable_children()->at(0);
            auto& rightChild = node->mutable_children()->at(1);

            continueLoop = visitCallback(&leftChild, depth + 1) &&
                           visitCallback(&rightChild, depth + 1) &&
                           visitCallback(node, depth);
            break;
        }

        default:
            throw std::runtime_error(
                "In order scan have sense onlyt on binary trees");
    }
    return continueLoop;
}

}  // namespace

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
