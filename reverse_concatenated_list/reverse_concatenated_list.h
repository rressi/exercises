#pragma once

#include <memory>
#include <vector>

namespace reverse_concatenated_list {

template<class T>
using Ptr = std::unique_ptr<T>;

struct ListNode {
    std::string value{};
    Ptr<ListNode> next{};
};

auto createList( std::vector<std::string> values) -> Ptr<ListNode>;

auto reverseList(Ptr<ListNode> head) -> Ptr<ListNode>;

auto compareLists(const ListNode &a, const ListNode &b) -> int;


} // namespace reverse_concatenated_list

