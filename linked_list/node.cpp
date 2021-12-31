#include "node.h"

#include <algorithm>
#include <cassert>
#include <set>

#include "node_iterator.h"


namespace linked_list {

auto createNode(std::string value) -> Node {
    auto newNode = Node();
    newNode.set_value(std::move(value));
    return newNode;
}

auto createList(std::vector<std::string> values) -> Opt<Node> {
    if (values.empty()) return {};

    auto newList = createNode(std::move(values.front()));
    auto tail = &newList;
    for (auto i = 1U; i < values.size(); i++) {
        tail = tail->mutable_next();
        tail->set_value(std::move(values[i]));
    }

    return newList;
}

auto reverseList(Node list) -> Node {
    auto values = traverseList(list);
    std::reverse(values.begin(), values.end());
    return std::move(createList(std::move(values)).value());
}

auto compareLists(const Node& a, const Node& b) -> int {
    return std::lexicographical_compare(begin(a), end(a), begin(b), end(b));
}

auto findNLastNode(const Node& list, std::size_t n) -> const Node* {
    auto fastRunner = begin(list);
    while (n > 0 && fastRunner->has_next()) {
        fastRunner++;
        n--;
    }
    if (n > 0) {
        return nullptr;
    }

    auto slowRunner = begin(list);
    while (fastRunner->has_next()) {
        fastRunner++;
        slowRunner++;
    }

    return &(*slowRunner);
}

void traverseList(const Node& list, const ValueCallback& valueCallback) {
    for (auto& node : list) {
        valueCallback(node.value());
    }
}

auto traverseList(const Node& list) -> std::vector<std::string> {
    auto values = std::vector<std::string>();
    for (auto& node : list) {
        values.push_back(node.value());
    }

    return values;
}

void traverseListInReverseOrder(const Node& list,
                                const ValueCallback& valueCallback) {
    auto stack = traverseList(list);
    while (!stack.empty()) {
        valueCallback(stack.back());
        stack.pop_back();
    }
}

void removeDuplicates(Node* list) {
    auto foundItems = std::set<std::string>();
    auto fastIt = begin(*list);
    auto slowIt = fastIt;
    auto tailIt = slowIt;
    while (fastIt != end(*list)) {
        const auto& value = fastIt->value();
        if (foundItems.count(value) == 0) {
            foundItems.insert(value);
            if (fastIt != slowIt) {
                slowIt->set_value(value);
            }
            tailIt = slowIt;
            slowIt++;
        }
        fastIt++;
    }
    tailIt->clear_next();
}

void removeDuplicatesSortedList(Node* list) {
    auto fastIt = begin(*list);
    if (!fastIt->has_next()) {
        return;
    }

    auto slowIt = fastIt;

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

    if (slowIt != end(*list)) {
        slowIt->clear_next();
    }
}

auto mergeSort(const Node& list) -> Node {
    auto [head, tail] = splitListInTwoHalves(list);
    if (!tail) {
        return head;
    }

    return mergeSortedLists(mergeSort(head), mergeSort(*tail));
}

auto splitListInTwoHalves(Node list) -> std::tuple<Node, Opt<Node>> {
    auto fastRunner = begin(list);
    auto slowRunner = fastRunner;

    auto i = 0;
    while (fastRunner->has_next()) {
        fastRunner++;
        if (i & 1) slowRunner++;
        i++;
    }

    if (auto tail = slowRunner->release_next()) {
        return {std::move(list), std::move(*tail)};
    }

    return {std::move(list), {}};
}

auto mergeSortedLists(const Node& listA, const Node& listB) -> Node {
    auto itA = begin(listA);
    auto itB = begin(listB);

    if (*itB < *itA) {
        std::swap(itA, itB);
    }

    Node mergedList(*itA);
    itA++;

    auto mergedTail = &mergedList;
    while (itA != end(listA) && itB != end(listB)) {
        if (*itB < *itA) {
            std::swap(itA, itB);
        }
        mergedTail = mergedTail->mutable_next();
        mergedTail->set_value(itA->value());
        itA++;
    }

    while (itA != end(listA)) {
        mergedTail = mergedTail->mutable_next();
        mergedTail->set_value(itA->value());
        itA++;
    }

    while (itB != end(listB)) {
        mergedTail = mergedTail->mutable_next();
        mergedTail->set_value(itB->value());
        itB++;
    }

    return mergedList;
}

}  // namespace linked_list
