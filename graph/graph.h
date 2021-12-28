#pragma once

#include <deque>
#include <vector>

namespace graph {

using Edge = int;
using Edges = std::vector<Edge>;

enum class Color { Black, Blue, Green, Orange, Red, Yellow, White };

struct Node {
    Color color{};
    std::vector<Edge> edges{};
};
using Graph = std::vector<Node>;

using ColorList = std::vector<Color>;

bool has_path(const Graph &graph, const ColorList &colorList);

}  // namespace graph
