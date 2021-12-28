#include "concatenated_list.h"

#include <cassert>
#include <set>

namespace concatenated_list {

auto createNode(std::string value, Ptr<ListNode> tail = {}) -> Ptr<ListNode> {
    auto newNode = std::make_unique<ListNode>();
    newNode->value = std::move(value);
    assert(newNode->size == 0);

    if (tail) {
        newNode->size += (1 + tail->size);
        newNode->next = std::move(tail);
    }

    return newNode;
}

auto createList(std::vector<std::string> values) -> Ptr<ListNode> {
    auto head = Ptr<ListNode>();

    while (!values.empty()) {
        head = createNode(std::move(values.back()), std::move(head));
        values.pop_back();
    }

    return head;
}

auto reverseList(Ptr<ListNode> head) -> Ptr<ListNode> {
    auto a = std::move(head);
    if (a) {
        auto b = std::move(a->next);
        assert(a->next == nullptr);

        a->size = 0;
        while (b) {
            auto c = std::move(b->next);
            b->size = 1 + a->size;
            b->next = std::move(a);
            a = std::move(b);
            b = std::move(c);
        }
    }

    return a;
}

auto compareLists(const ListNode& a, const ListNode& b) -> int {
    auto itA = &a;
    auto itB = &b;
    while (itA && itB) {
        if (auto r = itA->value.compare(itB->value)) {
            return r;
        }

        itA = itA->next.get();
        itB = itB->next.get();
    }

    if (itA) {
        return -1;
    } else if (itB) {
        return 1;
    }

    return 0;
}

auto findNLastNode(const ListNode& a, std::size_t n) -> const ListNode* {
    auto itA = &a;
    while (itA && itA->size > n) {
        itA = itA->next.get();
    }

    return (itA && itA->size == n) ? itA : nullptr;
}

void traverseList(const ListNode& head, const ValueCallback& valueCallback) {
    auto node = &head;
    while (node) {
        valueCallback(node->value);
        node = node->next.get();
    }
}

auto traverseList(const ListNode& head) -> std::vector<std::string> {
    auto values = std::vector<std::string>();
    values.reserve(head.size);

    auto node = &head;
    while (node) {
        values.push_back(node->value);
        node = node->next.get();
    }

    return values;
}

void traverseListInReverseOrder(const ListNode& head,
                                const ValueCallback& valueCallback) {
    auto stack = std::vector<std::string>();
    stack.reserve(head.size);

    traverseList(
        head, [&stack](const std::string& value) { stack.push_back(value); });

    while (!stack.empty()) {
        valueCallback(stack.back());
        stack.pop_back();
    }
}

void removeNextNode(ListNode* node) {
    if (node->next) {
        node->next = std::move(node->next->next);
    }
}

void removeDuplicates(ListNode* head) {
    auto foundItems = std::set<std::string>();
    auto node = head;
    while (node) {
        foundItems.insert(node->value);
        while (node->next && foundItems.count(node->next->value)) {
            removeNextNode(node);
        }
        node = node->next.get();
    }
}

}  // namespace concatenated_list
