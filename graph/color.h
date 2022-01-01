#pragma once

#include <deque>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace graph {

enum class Color { Black, Blue, Green, Orange, Red, Yellow, White };
using ColorList = std::vector<Color>;

auto toString(Color color) -> std::string;
auto toString(const ColorList& colorList) -> std::string;

}  // namespace graph
