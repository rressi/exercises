#include "graph.h"

#include <cassert>
#include <stdexcept>

#include "are_connected.h"
#include "has_path.h"


namespace graph {

auto Graph::addNode(Color color) -> NodeId {
  auto nodeId = nextNodeId_;
  nextNodeId_++;
  nodesByColor_[color].insert(nodeId);
  return nodeId;
}

void Graph::addEdge(NodeId source, NodeId destination) {
  if (source >= nextNodeId_) {
    throw std::runtime_error("Invalid source node id");
  }
  if (destination >= nextNodeId_) {
    throw std::runtime_error("Invalid destination node id");
  }
  nodesBySource_[source].insert(destination);
  nodesByDestination_[destination].insert(source);
}

auto Graph::findNodesByColor(Color color) const -> const NodeIds& {
  auto nodesByColorIt = nodesByColor_.find(color);
  if (nodesByColorIt == nodesByColor_.end()) {
    static const auto NO_NODE_IDS = NodeIds();
    return NO_NODE_IDS;
  }
  return nodesByColorIt->second;
}

auto Graph::findNodesBySource(NodeId sourceNode) const -> const NodeIds& {
  auto edgesIt = nodesBySource_.find(sourceNode);
  if (edgesIt == nodesBySource_.end()) {
    static const auto NO_NODE_IDS = NodeIds();
    return NO_NODE_IDS;
  }
  return edgesIt->second;
}

auto Graph::findNodesByDestination(NodeId destinationNode) const
    -> const NodeIds& {
  auto edgesIt = nodesByDestination_.find(destinationNode);
  if (edgesIt == nodesByDestination_.end()) {
    static const auto NO_NODE_IDS = NodeIds();
    return NO_NODE_IDS;
  }
  return edgesIt->second;
}

bool Graph::hasPath(const ColorList& colorList) const {
  return graph::hasPath(*this, colorList);
}

bool Graph::areConnected(NodeId source, NodeId destination) const {
  return graph::areConnected(*this, source, destination);
}

}  // namespace graph
