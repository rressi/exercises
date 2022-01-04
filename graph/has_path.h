#pragma once

#include <cassert>
#include <memory>
#include <optional>
#include <queue>
#include <set>
#include <tuple>
#include <vector>

#include "graph.h"

namespace graph {

bool hasPath(const Graph& graph, const ColorList& colorList);

}  // namespace graph
