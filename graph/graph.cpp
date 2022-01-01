#include "graph.h"

#include <cassert>
#include <stdexcept>

namespace graph {

auto Graph::addNode(Color color) -> NodeId {
    auto nodeId = nextNodeId_;
    nextNodeId_++;
    nodes_[color].insert(nodeId);
    return nodeId;
}

void Graph::addEdge(NodeId source, NodeId destination) {
    if (source >= nextNodeId_) {
        throw std::runtime_error("Invalid source node id");
    }
    if (destination >= nextNodeId_) {
        throw std::runtime_error("Invalid destination node id");
    }
    edges_[source].insert(destination);
}

class Graph::Runner {
   public:
    Runner(NodeId nodeId, const Color *queuedColors,
           std::size_t numQueuedColors, VisitedNodes visitedNodes)
        : nodeId_(nodeId),
          queuedColors_(queuedColors),
          numQueuedColors_(numQueuedColors),
          visitedNodes_(std::move(visitedNodes)) {}

   private:
    NodeId nodeId_{};
    const Color *queuedColors_{};
    std::size_t numQueuedColors_{};
    VisitedNodes visitedNodes_{};

    friend class Graph;
};

bool Graph::hasPath(const ColorList &colorList) const {
    auto [pathFound, runners] = createSeedRunners(colorList);
    if (pathFound) return true;

    while (!runners.empty()) {
        auto runner = std::move(runners.front());
        runners.pop_front();

        auto [pathFound, newRunners] = nextRunnerStep(runner);
        if (pathFound) return true;

        runners.insert(runners.end(), newRunners.begin(), newRunners.end());
    }

    return false;
}

auto Graph::nodesWithColor(Color color) const -> const NodeIds & {
    auto nodesByColorIt = nodes_.find(color);
    if (nodesByColorIt == nodes_.end()) {
        static const auto NO_NODE_IDS = NodeIds();
        return NO_NODE_IDS;
    }
    return nodesByColorIt->second;
}

auto Graph::nodesFromNode(NodeId nodeId) const -> const NodeIds & {
    auto edgesIt = edges_.find(nodeId);
    if (edgesIt == edges_.end()) {
        static const auto NO_NODE_IDS = NodeIds();
        return NO_NODE_IDS;
    }
    return edgesIt->second;
}

auto Graph::createSeedRunners(const ColorList &colorList) const
    -> std::tuple<bool, std::deque<Runner>> {
    if (colorList.empty()) return {};

    const auto &nodesWithFirstColor = nodesWithColor(colorList.front());
    if (nodesWithFirstColor.empty()) return {};
    if (colorList.size() == 1) return {true, {}};

    auto seedRunners = std::deque<Runner>();
    for (auto nodeId : nodesWithFirstColor) {
        seedRunners.emplace_back(nodeId, colorList.data() + 1,
                                 colorList.size() - 1, VisitedNodes{nodeId});
    }

    return {false, seedRunners};
}

auto Graph::nextRunnerStep(const Runner &runner) const
    -> std::tuple<bool, std::vector<Runner>> {
    const auto &nextNodeIds = nodesFromNode(runner.nodeId_);
    if (nextNodeIds.empty()) return {};

    assert(runner.numQueuedColors_ > 0);
    const auto &nodesWithNextColor = nodesWithColor(runner.queuedColors_[0]);

    auto nextRunners = std::vector<Runner>();
    for (auto nextNodeId : nextNodeIds) {
        if (runner.visitedNodes_.count(nextNodeId)) {
            continue;
        }

        auto queuedColors = runner.queuedColors_;
        auto numQueuedColors = runner.numQueuedColors_;
        auto visitedNodes = VisitedNodes();

        if (nodesWithNextColor.count(nextNodeId)) {
            queuedColors++;
            numQueuedColors--;
            if (numQueuedColors == 0) return {true, {}};
        } else {
            visitedNodes = runner.visitedNodes_;
        }
        visitedNodes.insert(nextNodeId);

        nextRunners.emplace_back(nextNodeId, queuedColors, numQueuedColors,
                                 std::move(visitedNodes));
    }

    return {false, std::move(nextRunners)};
}

}  // namespace graph
