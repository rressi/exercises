#include "list.h"

#include <algorithm>
#include <stdexcept>
#include <utility>


namespace linked_list {

List::List(NodeIteratorConst itStart, NodeIteratorConst itEnd) {
    auto it = itStart;
    while (it != itEnd) {
        append(it->value());
        it++;
    }
}

List::List(std::vector<Value> values) {
    for (auto&& value : values) {
        append(std::move(value));
    }
}

List::List(const List& other) : size_(other.size_), isSorted_(other.isSorted_) {
    operator=(other);
}

List::List(Ptr<Node> head, Node* tail, std::size_t size, bool isSorted)
    : head_(std::move(head)), tail_(tail), size_(size), isSorted_(isSorted) {}

auto List::operator=(const List& other) -> List& {
    if (other.head_) {
        head_ = std::make_unique<Node>(*(other.head_));
    } else {
        head_.reset();
    }

    size_ = other.size_;
    isSorted_ = other.isSorted_;
    tail_ = head_.get();

    return *this;
}

void List::append(Value newValue) {
    if (!head_) {
        assert(tail_ == nullptr);
        assert(size_ == 0);

        head_ = std::make_unique<Node>();
        tail_ = head_.get();
    } else {
        assert(tail_ != nullptr);
        assert(size_ > 0);

        isSorted_ = isSorted_ && bool(newValue >= tail_->value());
        tail_ = tail_->mutable_next();
    }

    tail_->set_value(std::move(newValue));
    size_++;
}

auto List::compare(const List& other) const -> int {
    return std::lexicographical_compare(begin(), end(),  //
                                        other.begin(), other.end());
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

    auto a = std::move(head_);
    tail_ = a.get();
    isSorted_ = true;

    auto b = Ptr<Node>(a->release_next());
    while (b) {
        auto c = Ptr<Node>(b->release_next());
        b->set_allocated_next(a.release());
        isSorted_ = isSorted_ && bool(b->value() <= b->next().value());
        a = std::move(b);
        b = std::move(c);
    }
    head_ = std::move(a);
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

auto List::mergeSortedLists(const List& a, const List& b) -> List {
    if (!a.isSorted_) {
        throw std::runtime_error("This list is not sorted");
    } else if (!b.isSorted_) {
        throw std::runtime_error("The passed list is not sorted");
    } else if (a.empty()) {
        return b;
    } else if (b.empty()) {
        return a;
    }

    auto aIt = a.begin();
    auto aEnd = a.end();
    auto bIt = b.begin();
    auto bEnd = b.end();
    if (bIt->value() < aIt->value()) {
        std::swap(aIt, bIt);
        std::swap(aEnd, bEnd);
    }

    auto newHead = std::make_unique<Node>();
    auto newTail = newHead.get();
    newTail->set_value(aIt->value());
    aIt++;

    while (aIt != aEnd && bIt != bEnd) {
        if (bIt->value() < aIt->value()) {
            std::swap(aIt, bIt);
            std::swap(aEnd, bEnd);
        }
        newTail = newTail->mutable_next();
        newTail->set_value(aIt->value());
        aIt++;
    }

    if (aIt == aEnd) {
        std::swap(aIt, bIt);
        std::swap(aEnd, bEnd);
    }

    while (aIt != aEnd) {
        newTail = newTail->mutable_next();
        newTail->set_value(aIt->value());
        aIt++;
    }

    return List(std::move(newHead), newTail, a.size() + b.size(), true);
}

void List::sort() {
    if (size_ <= 1) {
        return;
    }

    auto [left, right] = std::move(*this).split();
    left.sort();
    right.sort();
    operator=(List::mergeSortedLists(left, right));
}

}  // namespace linked_list
