#pragma once

#include <functional>
#include <iterator>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

#include "node.pb.h"


namespace linked_list {

template <class T>
using Opt = std::optional<T>;

class Node;

inline bool operator<(const Node& a, const Node& b) {
    return a.value() < b.value();
}

auto createNode(std::string value) -> Node;
auto createList(std::vector<std::string> values) -> Opt<Node>;

auto reverseList(Node head) -> Node;

auto compareLists(const Node& a, const Node& b) -> int;

auto findNLastNode(const Node& list, std::size_t n) -> const Node*;

using ValueCallback = std::function<void(const std::string&)>;
auto traverseList(const Node& list) -> std::vector<std::string>;
void traverseList(const Node& list, const ValueCallback& valueCallback);
void traverseListInReverseOrder(const Node& list,
                                const ValueCallback& valueCallback);

void removeDuplicates(Node* list);
void removeDuplicatesSortedList(Node* list);

auto mergeSort(const Node& list) -> Node;
auto mergeSortedLists(const Node& listA, const Node& listB) -> Node;
auto splitListInTwoHalves(Node list) -> std::tuple<Node, Opt<Node>>;

class ConstNodeIt {
   public:
    using Node = linked_list::Node;

    using difference_type = std::ptrdiff_t;
    using value_type = Node;
    using pointer = const Node*;
    using reference = const Node&;
    using iterator_category = std::input_iterator_tag;

    ConstNodeIt() = default;
    ConstNodeIt(const Node* node) : node_(node) {}

    auto operator++() -> ConstNodeIt {
        advance();
        return *this;
    }
    auto operator++(int) -> ConstNodeIt {
        auto originalValue = ConstNodeIt(*this);
        advance();
        return originalValue;
    }
    auto operator*() const -> const Node& { return *node_; }
    auto operator-> () const -> const Node* { return node_; }
    bool operator==(const ConstNodeIt& other) const {
        return node_ == other.node_;
    }
    bool operator!=(const ConstNodeIt& other) const {
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

class MutableNodeIt {
   public:
    using Node = linked_list::Node;

    using difference_type = std::ptrdiff_t;
    using value_type = Node;
    using pointer = Node*;
    using reference = Node&;
    using iterator_category = std::input_iterator_tag;

    MutableNodeIt() = default;
    MutableNodeIt(Node* node) : node_(node) {}

    auto operator++() -> MutableNodeIt {
        advance();
        return *this;
    }
    auto operator++(int) -> MutableNodeIt {
        auto originalValue = MutableNodeIt(*this);
        advance();
        return originalValue;
    }
    auto operator*() const -> Node& { return *node_; }
    auto operator-> () const -> Node* { return node_; }
    bool operator==(const MutableNodeIt& other) const {
        return node_ == other.node_;
    }
    bool operator!=(const MutableNodeIt& other) const {
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

inline auto begin(const Node& node) -> ConstNodeIt { return {&node}; }
inline auto end(const Node& node) -> ConstNodeIt { return {}; }
inline auto begin(Node& node) -> MutableNodeIt { return {&node}; }
inline auto end(Node& node) -> MutableNodeIt { return {}; }

}  // namespace linked_list
