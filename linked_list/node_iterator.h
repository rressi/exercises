#pragma once

#include <cstddef>
#include <iterator>

#include "node.h"

namespace linked_list {

class NodeIteratorConst {
   public:
    using Node = linked_list::Node;

    using difference_type = std::ptrdiff_t;
    using value_type = Node;
    using pointer = const Node*;
    using reference = const Node&;
    using iterator_category = std::input_iterator_tag;

    NodeIteratorConst() = default;
    NodeIteratorConst(const Node* node) : node_(node) {}

    auto operator++() -> NodeIteratorConst {
        advance();
        return *this;
    }
    auto operator++(int) -> NodeIteratorConst {
        auto originalValue = NodeIteratorConst(*this);
        advance();
        return originalValue;
    }
    auto operator*() const -> const Node& { return *node_; }
    auto operator-> () const -> const Node* { return node_; }
    bool operator==(const NodeIteratorConst& other) const {
        return node_ == other.node_;
    }
    bool operator!=(const NodeIteratorConst& other) const {
        return node_ != other.node_;
    }

   private:
    const Node* node_{};
    void advance() {
        if (node_) {
            if (node_->has_next()) {
                node_ = &(node_->next());
            } else {
                node_ = nullptr;
            }
        }
    }
};

class NodeIteratorMutable {
   public:
    using Node = linked_list::Node;

    using difference_type = std::ptrdiff_t;
    using value_type = Node;
    using pointer = Node*;
    using reference = Node&;
    using iterator_category = std::input_iterator_tag;

    NodeIteratorMutable() = default;
    NodeIteratorMutable(Node* node) : node_(node) {}

    auto operator++() -> NodeIteratorMutable {
        advance();
        return *this;
    }
    auto operator++(int) -> NodeIteratorMutable {
        auto originalValue = NodeIteratorMutable(*this);
        advance();
        return originalValue;
    }
    auto operator*() const -> Node& { return *node_; }
    auto operator-> () const -> Node* { return node_; }
    bool operator==(const NodeIteratorMutable& other) const {
        return node_ == other.node_;
    }
    bool operator!=(const NodeIteratorMutable& other) const {
        return node_ != other.node_;
    }

   private:
    Node* node_{};
    void advance() {
        if (node_) {
            if (node_->has_next()) {
                node_ = node_->mutable_next();
            } else {
                node_ = nullptr;
            }
        }
    }
};

inline auto begin(const Node& node) -> NodeIteratorConst { return {&node}; }
inline auto end(const Node& node) -> NodeIteratorConst { return {}; }
inline auto begin(Node& node) -> NodeIteratorMutable { return {&node}; }
inline auto end(Node& node) -> NodeIteratorMutable { return {}; }

}  // namespace linked_list
