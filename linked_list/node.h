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

}  // namespace linked_list
