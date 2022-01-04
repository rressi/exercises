#pragma once

#include "graph.h"

namespace graph {

bool areConnected(const Graph& graph, Graph::NodeId source,
                  Graph::NodeId destination);

}  // namespace graph
