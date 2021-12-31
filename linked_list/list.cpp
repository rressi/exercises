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

auto List::reverse() {
    auto a = Ptr<Node>(head_.release());
    head_.reset(tail_);
    isSorted_ = true;
    if (a) {
        auto b = Ptr<Node>(a->release_next());
        while (b) {
            auto c = Ptr<Node>(b->release_next());
            b->set_allocated_next(a.release());
            isSorted_ = isSorted_ && bool(b->value() <= b->next().value());
            a = std::move(b);
            b = std::move(c);
        }
    }
    tail_ = a.get();
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
        auto foundItems = std::set<Value>();
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
    assert(slowRunner->has_next());

    return {List(std::move(head_), &*(slowRunner), size_ / 2, isSorted_),
            List(Ptr<Node>(slowRunner->release_next()), &*(fastRunner),
                 size_ - (size_ / 2), isSorted_)};
}

auto List::mergeSorted(const List& other) {
    if (!isSorted_) {
        throw std::runtime_error("This list is not sorted");
    } else if (!other.isSorted_) {
        throw std::runtime_error("The passed list is not sorted");
    } else if (other.empty()) {
        return;
    } else if (empty()) {
        operator=(other);
        return;
    }

    auto newHead = Ptr<Node>();
    auto newTail = newHead.get();
    auto otherIt = other.begin();

    const auto& value = otherIt->value();
    if (value >= head_->value()) {
        newTail = newTail->mutable_next();
        newTail->set_value(value);
        otherIt++;
    } else {
        newHead = std::move(head_);
        head_.reset(newHead->release_next());
    }

    while (head_) {
        const auto& value = otherIt->value();
        if (value >= head_->value()) {
            newTail = newTail->mutable_next();
            newTail->set_value(value);
            otherIt++;
        } else {
            newTail->set_allocated_next(head_.release());
            newTail = newTail->mutable_next();
            head_.reset(newTail->release_next());
        }
    }

    while (otherIt != other.end()) {
        newTail = newTail->mutable_next();
        newTail->set_value(value);
        otherIt++;
    }

    head_ = std::move(newHead);
    tail_ = newTail;
    size_ += other.size_;
}

void List::sort() {
    if (size_ <= 1) {
        return;
    }

    auto [left, right] = std::move(*this).split();
    left.mergeSorted(right);
    operator=(left);
}

}  // namespace linked_list
