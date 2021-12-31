#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

#include "node.h"
#include "node_iterator.h"

namespace linked_list {

template <class T>
using Ptr = std::unique_ptr<T>;

class List final {
   public:
    using Value = std::string;
    using ValueCallback = std::function<void(const std::string&)>;

    List() = default;
    List(NodeIteratorConst itStart, NodeIteratorConst itEnd);
    List(std::vector<Value> values);
    List(const List&);
    List(List&&) noexcept = default;
    auto operator=(const List&) -> List&;
    auto operator=(List&&) noexcept -> List& = default;

    auto compare(const List& other) const -> int;
    bool empty() const { return !head_; };
    auto extractValues() const -> std::vector<Value>;
    auto head() const -> const Node* { return head_.get(); }
    bool isSorted() const { return isSorted_; }
    auto size() const { return size_; }
    auto tail(std::size_t n = 0) const -> const Node* { return tail_; }

    void visitValues(const ValueCallback& valueCallback) const;
    void visitValuesReverse(const ValueCallback& valueCallback) const;

    void append(Value newValue);
    auto reverse();
    void removeDuplicates();
    void sort();
    auto split() && -> std::tuple<List, List>;
    auto mergeSorted(const List&);

    auto begin() const -> NodeIteratorConst {
        return NodeIteratorConst(head_.get());
    }
    auto end() const -> NodeIteratorConst { return NodeIteratorConst(); }
    auto cbegin() const -> NodeIteratorConst {
        return NodeIteratorConst(head_.get());
    }
    auto cend() const -> NodeIteratorConst { return NodeIteratorConst(); }

    auto begin() -> NodeIteratorMutable {
        return NodeIteratorMutable(head_.get());
    }
    auto end() -> NodeIteratorMutable { return NodeIteratorMutable(); }

    auto splitListInTwoHalves(Node list) -> std::tuple<Node, Opt<Node>>;

   private:
    Ptr<Node> head_{};
    Node* tail_{};
    std::size_t size_{};
    bool isSorted_{true};

    List(Ptr<Node> head, Node* tail, std::size_t size, bool isSorted);
};

inline bool operator<(const List& a, const List& b) { return a.compare(b) < 0; }

}  // namespace linked_list
