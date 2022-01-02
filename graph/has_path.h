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

template <class T>
using Opt = std::optional<T>;

template <class T>
using Set = std::set<T>;

template <class T>
using Queue = std::priority_queue<T>;

template <class T>
using Shared = std::shared_ptr<T>;

class HasPathTask {
   public:
    enum class Status { CONTINUE, FAIL, SUCCESS };

    static auto start(const Graph& graph, const ColorList& colorList,
                      Queue<HasPathTask>* taskQueue) -> Status;

    using ColorIndex = std::size_t;
    using NodeId = Graph::NodeId;
    using VisitedNodes = Set<std::tuple<NodeId, ColorIndex>>;

    HasPathTask() = default;
    HasPathTask(const Graph& graph, const ColorList& colorList,
                Shared<VisitedNodes> visitedNodes, NodeId nodeId,
                ColorIndex colorIndex);
    HasPathTask(const HasPathTask& other) = default;
    ~HasPathTask() = default;

    auto operator=(const HasPathTask& other) -> HasPathTask& = default;
    bool operator<(const HasPathTask& other) const;

    auto execute(Queue<HasPathTask>* taskQueue) const -> Status;

   private:
    const Graph* graph_{};
    const ColorList* colorList_{};
    Shared<VisitedNodes> visitedNodes_{};

    NodeId nodeId_{};
    std::size_t colorIndex_{};
};

inline HasPathTask::HasPathTask(const Graph& graph, const ColorList& colorList,
                                Shared<VisitedNodes> visitedNodes,
                                NodeId nodeId, ColorIndex colorIndex)
    : graph_(&graph),
      colorList_(&colorList),
      visitedNodes_(visitedNodes),
      nodeId_(nodeId),
      colorIndex_(colorIndex) {
    assert(graph_ != nullptr);
    assert(colorList_ != nullptr);
}

inline bool HasPathTask::operator<(const HasPathTask& other) const {
    return colorIndex_ < other.colorIndex_;
}

}  // namespace graph
