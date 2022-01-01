#include "list.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace linked_list {

List::List(NodeIteratorConst itStart, NodeIteratorConst itEnd) {
    for (auto it = itStart; it != itEnd; it++) {
        push_back(it->value());
    }
}

List::List(std::vector<Value> values) {
    for (auto&& value : values) {
        push_back(std::move(value));
    }
}

List::List(const List& other) : size_(other.size_), isSorted_(other.isSorted_) {
    copyAssign(other);
}

List::List(Ptr<Node> head, Node* tail, std::size_t size, bool isSorted)
    : head_(std::move(head)), tail_(tail), size_(size), isSorted_(isSorted) {}

auto List::operator=(const List& other) -> List& {
    copyAssign(other);
    return *this;
}

auto List::compare(const List& other) const -> int {
    return std::lexicographical_compare(begin(), end(),  //
                                        other.begin(), other.end());
}

auto List::front() const -> const Value& {
    if (empty()) {
        throw std::runtime_error("Cannot return front value of an empty list");
    }
    return head_->value();
}

auto List::extractValues() const -> std::vector<Value> {
    auto values = std::vector<Value>();
    for (const auto& node : *this) {
        values.push_back(node.value());
    }
    return values;
}

auto List::tail(std::size_t n) const -> const Node* {
    if (n == 0) {
        return tail_;
    } else if (n >= size_) {
        return nullptr;
    }

    auto frontRunner = begin();
    while (n > 0 && frontRunner->has_next()) {
        frontRunner++;
        n--;
    }
    assert(n == 0);

    auto backRunner = begin();
    while (frontRunner->has_next()) {
        frontRunner++;
        backRunner++;
    }
    assert(backRunner->has_next());

    return &(*backRunner);
}

void List::visitValues(const ValueCallback& valueCallback) const {
    for (const auto& node : *this) {
        valueCallback(node.value());
    }
}

void List::visitValuesReverse(const ValueCallback& valueCallback) const {
    auto stack = extractValues();
    while (!stack.empty()) {
        valueCallback(stack.back());
        stack.pop_back();
    }
}

void List::reverse() {
    if (size_ <= 1) return;

    auto reversedList = List();
    while (!empty()) {
        reversedList.pushFront(popFront());
    }

    operator=(std::move(reversedList));
}

void List::removeDuplicates() {
    if (empty()) {
        return;
    }
    auto fastIt = begin();
    auto slowIt = fastIt;

    if (isSorted_) {
        while (fastIt->has_next()) {
            const auto& referenceValue = fastIt->value();
            const auto& newValue = fastIt->next().value();
            fastIt++;

            if (referenceValue != newValue) {
                slowIt++;
                if (fastIt != slowIt) {
                    slowIt->set_value(newValue);
                }
            }
        }
    } else {
        auto foundItems = std::set<Value>{fastIt->value()};
        while (fastIt->has_next()) {
            fastIt++;
            const auto& newValue = fastIt->value();
            if (foundItems.count(newValue) == 0) {
                foundItems.insert(newValue);
                slowIt++;
                if (fastIt != slowIt) {
                    slowIt->set_value(newValue);
                }
            }
        }
    }

    if (slowIt != end()) {
        slowIt->clear_next();
    }
}

void List::sort() {
    if (isSorted_) {
        return;
    }

    assert(size_ > 1);
    auto [left, right] = std::move(*this).split();

    left.sort();
    right.sort();

    auto mergedList = List::mergeSortedLists(std::move(left), std::move(right));
    assert(mergedList.isSorted());

    operator=(std::move(mergedList));
}

auto List::split() && -> std::tuple<List, List> {
    if (size_ <= 1) {
        return {std::move(*this), {}};
    }

    auto fastRunner = begin();
    auto slowRunner = fastRunner;

    auto i = 0;
    while (fastRunner->has_next()) {
        fastRunner++;
        if (i & 1) slowRunner++;
        i++;
    }

    auto tailSize = size_ / 2;
    auto headSize = size_ - tailSize;

    auto left = List(std::move(head_), &*(slowRunner), headSize,
                     isSorted_ || headSize == 1);
    auto right = List(Ptr<Node>(slowRunner->release_next()), &*(fastRunner),
                      tailSize, isSorted_ || tailSize == 1);

    return std::tuple<List, List>(std::move(left), std::move(right));
}

auto List::mergeSortedLists(List a, List b) -> List {
    if (!a.isSorted_) {
        throw std::runtime_error("This list is not sorted");
    } else if (!b.isSorted_) {
        throw std::runtime_error("The passed list is not sorted");
    } else if (a.empty()) {
        return b;
    } else if (b.empty()) {
        return a;
    }

    auto newList = List();
    while (!a.empty() && !b.empty()) {
        if (b.front() < a.front()) {
            newList.pushBack(b.popFront());
        } else {
            newList.pushBack(a.popFront());
        }
    }
    while (!a.empty()) {
        newList.pushBack(a.popFront());
    }
    while (!b.empty()) {
        newList.pushBack(b.popFront());
    }

    return newList;
}

auto List::pop_front() -> Value {
    if (empty()) {
        throw std::runtime_error("Cannot pop front value of an empty list");
    }
    return popFront()->value();
}

void List::push_front(Value newValue) {
    auto newNode = std::make_unique<Node>();
    newNode->set_value(std::move(newValue));
    pushFront(std::move(newNode));
}

void List::push_back(Value newValue) {
    auto newNode = std::make_unique<Node>();
    newNode->set_value(std::move(newValue));
    pushBack(std::move(newNode));
}

auto List::popFront() -> Ptr<Node> {
    if (!head_) return {};

    auto nextNode = std::move(head_);
    if (nextNode->has_next()) {
        head_.reset(nextNode->release_next());
    } else {
        tail_ = nullptr;
    }

    size_--;
    isSorted_ = isSorted_ || size_ <= 1;
    return nextNode;
}

void List::pushFront(Ptr<Node> newNode) {
    if (!newNode) return;

    auto newNodeTail = newNode.get();
    auto newNodeSize = std::size_t(1);
    auto newNodeIsSorted = true;

    while (newNodeTail->has_next()) {
        newNodeSize++;
        newNodeIsSorted = newNodeIsSorted && bool(newNodeTail->value() <=
                                                  newNodeTail->next().value());
        newNodeTail = newNodeTail->mutable_next();
    }

    if (head_) {
        newNodeTail->set_allocated_next(head_.release());
        newNodeIsSorted =
            newNodeIsSorted && isSorted_ &&
            bool(newNodeTail->value() <= newNodeTail->next().value());
    } else {
        tail_ = newNodeTail;
    }

    head_ = std::move(newNode);
    size_ += newNodeSize;
    isSorted_ = newNodeIsSorted;
}

void List::pushBack(Ptr<Node> newNode) {
    if (!newNode) return;

    auto newNodeTail = newNode.get();
    auto newNodeSize = std::size_t(1);
    auto newNodeIsSorted = true;

    while (newNodeTail->has_next()) {
        newNodeSize++;
        newNodeIsSorted = newNodeIsSorted && bool(newNodeTail->value() <=
                                                  newNodeTail->next().value());
        newNodeTail = newNodeTail->mutable_next();
    }

    if (tail_) {
        tail_->set_allocated_next(newNode.release());
        newNodeIsSorted = newNodeIsSorted && isSorted_ &&
                          bool(tail_->value() <= tail_->next().value());
    } else {
        head_ = std::move(newNode);
    }

    tail_ = newNodeTail;
    size_ += newNodeSize;
    isSorted_ = newNodeIsSorted;
}

void List::copyAssign(const List& other) {
    if (this == &other) return;

    if (other.head_) {
        head_ = std::make_unique<Node>(*(other.head_));
    } else {
        head_.reset();
    }

    tail_ = head_.get();
    size_ = other.size_;
    isSorted_ = other.isSorted_;
}

}  // namespace linked_list
