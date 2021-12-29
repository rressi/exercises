#include "concatenated_list.h"

#include <cassert>
#include <set>

namespace concatenated_list {

auto createNode(std::string value, Ptr<ListNode> tail = {}) -> Ptr<ListNode> {
    auto newNode = std::make_unique<ListNode>();
    newNode->value = std::move(value);

    if (tail) {
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

        while (b) {
            auto c = std::move(b->next);
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
    auto fastRunner = &a;
    while (n > 0 && fastRunner->next) {
        fastRunner = fastRunner->next.get();
        n--;
    }
    if (n > 0) {
        return nullptr;
    }

    auto slowRunner = &a;
    while (fastRunner->next) {
        fastRunner = fastRunner->next.get();
        slowRunner = slowRunner->next.get();
    }

    return slowRunner;
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

auto removeDuplicatesNoExtraMemory(Ptr<ListNode> list) -> Ptr<ListNode> {
    list = mergeSort(std::move(list));
    auto node = list.get();
    while (node) {
        while (node->next && node->value == node->next->value) {
            removeNextNode(node);
        }
        node = node->next.get();
    }
    return list;
}

auto splitListInTwoHalves(Ptr<ListNode> head)
    -> std::tuple<Ptr<ListNode>, Ptr<ListNode>> {
    if (!head) return {};

    auto fastRunner = head.get();
    auto slowRunner = fastRunner;

    auto i = 0;
    while (fastRunner->next) {
        fastRunner = fastRunner->next.get();
        if (i & 1) {
            slowRunner = slowRunner->next.get();
        }
        i++;
    }

    auto tail = std::move(slowRunner->next);
    slowRunner->next = nullptr;

    return std::make_tuple(std::move(head), std::move(tail));
}

namespace {

auto _mergeSortedLists(Ptr<ListNode> a, Ptr<ListNode> b) -> Ptr<ListNode> {
    if (!a) return b;
    if (!b) return a;

    if (a->value > b->value) {
        std::swap(a, b);
    }

    auto mergedHead = std::move(a);
    a = std::move(mergedHead->next);

    auto mergedTail = mergedHead.get();
    while (a && b) {
        if (a->value > b->value) {
            std::swap(a, b);
        }

        mergedTail->next = std::move(a);
        mergedTail = mergedTail->next.get();
        a = std::move(mergedTail->next);
    }

    if (a) {
        mergedTail->next = std::move(a);
    } else if (b) {
        mergedTail->next = std::move(b);
    }

    return mergedHead;
}

}  // namespace

auto mergeSort(Ptr<ListNode> list) -> Ptr<ListNode> {
    if (!list) return {};
    if (!list->next) return list;

    auto [head, tail] = splitListInTwoHalves(std::move(list));
    head = mergeSort(std::move(head));
    tail = mergeSort(std::move(tail));
    return _mergeSortedLists(std::move(head), std::move(tail));
}

}  // namespace concatenated_list
