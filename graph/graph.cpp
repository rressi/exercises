#include "graph.h"

#include <cassert>
#include <stdexcept>

#include "has_path.h"

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

auto Graph::findNodesByColor(Color color) const -> const NodeIds& {
    auto nodesByColorIt = nodes_.find(color);
    if (nodesByColorIt == nodes_.end()) {
        static const auto NO_NODE_IDS = NodeIds();
        return NO_NODE_IDS;
    }
    return nodesByColorIt->second;
}

auto Graph::findLinkedNodes(NodeId nodeId) const -> const NodeIds& {
    auto edgesIt = edges_.find(nodeId);
    if (edgesIt == edges_.end()) {
        static const auto NO_NODE_IDS = NodeIds();
        return NO_NODE_IDS;
    }
    return edgesIt->second;
}

bool Graph::hasPath(const ColorList& colorList) const {
    return graph::hasPath(*this, colorList);
}

}  // namespace graph
