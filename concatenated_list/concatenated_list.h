#pragma once

#include <memory>
#include <vector>

namespace concatenated_list {

template<class T>
using Ptr = std::unique_ptr<T>;

struct ListNode {
    std::string value{};
    std::size_t size{};
    Ptr<ListNode> next{};
};

auto createList(std::vector<std::string> values) -> Ptr<ListNode>;

auto reverseList(Ptr<ListNode> head) -> Ptr<ListNode>;

auto compareLists(const ListNode &a, const ListNode &b) -> int;

auto findNLastNode(const ListNode &a, std::size_t n) -> const ListNode *;


} // namespace concatenated_list

