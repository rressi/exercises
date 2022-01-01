#pragma once

#include <deque>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace graph {

class Graph {
   public:
    enum class Color { Black, Blue, Green, Orange, Red, Yellow, White };
    using ColorList = std::vector<Color>;
    using NodeId = std::size_t;
    using NodeIds = std::unordered_set<NodeId>;

    auto addNode(Color color) -> NodeId;
    void addEdge(NodeId source, NodeId destination);

    bool hasPath(const ColorList &colorList) const;

    auto nodesWithColor(Color color) const -> const NodeIds &;
    auto nodesFromNode(NodeId nodeId) const -> const NodeIds &;

   private:
    NodeId nextNodeId_{};
    std::unordered_map<Color, NodeIds> nodes_{};
    std::unordered_map<NodeId, NodeIds> edges_{};

    struct Runner;
    using VisitedNodes = std::unordered_set<Graph::NodeId>;

    auto createSeedRunners(const ColorList &colorList) const
        -> std::tuple<bool, std::deque<Runner>>;
    auto nextRunnerStep(const Runner &runner) const
        -> std::tuple<bool, std::vector<Runner>>;
};

}  // namespace graph
