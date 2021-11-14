#include "concatenated_list.h"

#include <cassert>

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

    for (auto it = values.rbegin(); it != values.rend(); it++) {
        head = createNode(std::move(*it), std::move(head));
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

auto compareLists(const ListNode &a, const ListNode &b) -> int {

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

auto findNLastNode(const ListNode &a, std::size_t n) -> const ListNode * {

    auto itA = &a;
    while (itA && itA->size > n) {
        itA = itA->next.get();
    }

    return (itA && itA->size == n) ? itA
                                   : nullptr;
}

} // namespace concatenated_list
