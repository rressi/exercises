#pragma once

#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

namespace linked_list {

template <class T>
using Ptr = std::unique_ptr<T>;

struct ListNode {
    std::string value{};
    Ptr<ListNode> next{};
};

auto createList(std::vector<std::string> values) -> Ptr<ListNode>;

auto reverseList(Ptr<ListNode> head) -> Ptr<ListNode>;

auto compareLists(const ListNode& a, const ListNode& b) -> int;

auto findNLastNode(const ListNode& a, std::size_t n) -> const ListNode*;

using ValueCallback = std::function<void(const std::string&)>;
void traverseList(const ListNode& head, const ValueCallback& valueCallback);
auto traverseList(const ListNode& head) -> std::vector<std::string>;
void traverseListInReverseOrder(const ListNode& head,
                                const ValueCallback& valueCallback);

void removeNextNode(ListNode* node);
void removeDuplicates(ListNode* head);
auto removeDuplicatesNoExtraMemory(Ptr<ListNode> list) -> Ptr<ListNode>;

auto splitListInTwoHalves(Ptr<ListNode> head)
    -> std::tuple<Ptr<ListNode>, Ptr<ListNode>>;
auto mergeSort(Ptr<ListNode> a) -> Ptr<ListNode>;

}  // namespace linked_list
