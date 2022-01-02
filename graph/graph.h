#pragma once

#include <deque>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "color.h"

namespace graph {

class Graph {
   public:
    using NodeId = std::size_t;
    using NodeIds = std::unordered_set<NodeId>;

    auto addNode(Color color) -> NodeId;
    void addEdge(NodeId source, NodeId destination);

    auto findNodesByColor(Color color) const -> const NodeIds &;
    auto findLinkedNodes(NodeId nodeId) const -> const NodeIds &;

    bool hasPath(const ColorList &colorList) const;

   private:
    NodeId nextNodeId_{};
    std::unordered_map<Color, NodeIds> nodes_{};
    std::unordered_map<NodeId, NodeIds> edges_{};
};

}  // namespace graph
