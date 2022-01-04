#include "are_connected.h"

#include <cassert>
#include <functional>
#include <memory>
#include <queue>
#include <unordered_set>

namespace graph {
namespace {

template <class T>
using Queue = std::priority_queue<T>;

template <class T>
using Shared = std::shared_ptr<T>;

template <class T>
using Set = std::unordered_set<T>;

using Distance = std::size_t;
using NodeId = Graph::NodeId;
using NodeIds = Graph::NodeIds;
using VisitedNodes = Set<NodeId>;

enum class Status { CONTINUE, FAIL, SUCCESS };

class Task {
 public:
  Task() = default;

  using FindNodes = std::function<const NodeIds&(NodeId)>;

  Task(FindNodes findNodes, Shared<VisitedNodes> visitedFromSource,
       Shared<VisitedNodes> visitedFromDestination, NodeId source,
       NodeId destination, Distance distance);
  Task(const Task& other) = default;
  ~Task() = default;

  auto operator=(const Task& other) -> Task& = default;
  bool operator<(const Task& other) const {
    return other.distance_ < distance_;
  }

  static auto start(const Graph& graph, NodeId source, NodeId destination,
                    Queue<Task>* taskQueue) -> Status;
  static auto createVisitedNodes(NodeId firstNode, const NodeIds& nextNodes)
      -> Shared<VisitedNodes>;

  auto execute(Queue<Task>* taskQueue) const -> Status;

 private:
  FindNodes findNodes_{};
  Shared<VisitedNodes> visitedFromSource_{};
  Shared<VisitedNodes> visitedFromDestination_{};

  NodeId source_{};
  NodeId destination_{};
  Distance distance_{};
};

Task::Task(FindNodes findNodes, Shared<VisitedNodes> visitedFromSource,
           Shared<VisitedNodes> visitedFromDestination, NodeId source,
           NodeId destination, Distance distance)
    : findNodes_(std::move(findNodes)),
      visitedFromSource_(std::move(visitedFromSource)),
      visitedFromDestination_(std::move(visitedFromDestination)),
      source_(source),
      destination_(destination),
      distance_(distance) {
  assert(findNodes_ != nullptr);
  assert(visitedFromSource_ != nullptr);
  assert(visitedFromDestination_ != nullptr);
}

auto Task::start(const Graph& graph, NodeId source, NodeId destination,
                 Queue<Task>* taskQueue) -> Status {
  const auto& nodesFromSource = graph.findNodesBySource(source);
  if (nodesFromSource.empty()) {
    return Status::FAIL;
  } else if (nodesFromSource.count(destination)) {
    return Status::SUCCESS;
  }

  const auto& nodesFromDestination = graph.findNodesBySource(destination);
  if (nodesFromDestination.empty()) {
    return Status::FAIL;
  }

  auto visitedFromSource = Task::createVisitedNodes(source, nodesFromSource);
  auto visitedFromDestination =
      Task::createVisitedNodes(destination, nodesFromDestination);

  auto findNodesBySource = [&graph](NodeId nodeId) {
    return graph.findNodesBySource(nodeId);
  };
  auto findNodesByDestination = [&graph](NodeId nodeId) {
    return graph.findNodesByDestination(nodeId);
  };

  auto INITIAL_DISTANCE = Distance(1);
  for (auto nextNodeFromSource : nodesFromSource) {
    taskQueue->emplace(findNodesBySource, visitedFromSource,
                       visitedFromDestination, nextNodeFromSource, destination,
                       INITIAL_DISTANCE);
  }
  for (auto nextNodeFromDestination : nodesFromDestination) {
    taskQueue->emplace(findNodesByDestination, visitedFromDestination,
                       visitedFromSource, nextNodeFromDestination, source,
                       INITIAL_DISTANCE);
  }

  return Status::CONTINUE;
}

auto Task::createVisitedNodes(NodeId firstNode, const NodeIds& nextNodes)
    -> Shared<VisitedNodes> {
  auto visitedNodes = std::make_shared<VisitedNodes>();

  visitedNodes->insert(firstNode);
  for (auto nodeId : nextNodes) {
    visitedNodes->insert(nodeId);
  }

  return visitedNodes;
}

auto Task::execute(Queue<Task>* taskQueue) const -> Status {
  const auto& nextNodes = findNodes_(source_);
  if (nextNodes.empty()) return Status::CONTINUE;
  if (nextNodes.count(destination_)) return Status::SUCCESS;

  for (auto nodeId : nextNodes) {
    if (visitedFromDestination_->count(nodeId)) return Status::SUCCESS;

    auto [_, firstVisit] = visitedFromSource_->emplace(nodeId);
    if (firstVisit) {
      taskQueue->emplace(findNodes_, visitedFromSource_,
                         visitedFromDestination_, nodeId, destination_,
                         distance_ + 1);
    }
  }

  return Status::CONTINUE;
}

}  // namespace

bool areConnected(const Graph& graph, NodeId source, NodeId destination) {
  auto taskQueue = Queue<Task>();
  auto status = Task::start(graph, source, destination, &taskQueue);
  while (status == Status::CONTINUE  //
         && !taskQueue.empty()) {
    auto task = std::move(taskQueue.top());
    taskQueue.pop();
    status = task.execute(&taskQueue);
  }

  return bool(status == Status::SUCCESS);
}

}  // namespace graph
