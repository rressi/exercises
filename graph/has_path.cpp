
#include "has_path.h"

#include <cassert>
#include <memory>
#include <optional>
#include <queue>
#include <set>
#include <tuple>
#include <vector>


namespace graph {
namespace {

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
  enum class Status { CONTINUE, SUCCESS, FAIL };

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

  static auto start(const Graph& graph, const ColorList& colorList,
                    Queue<HasPathTask>* taskQueue) -> Status;

  auto execute(Queue<HasPathTask>* taskQueue) const -> Status;

 private:
  const Graph* graph_{};
  const ColorList* colorList_{};
  Shared<VisitedNodes> visitedNodes_{};

  NodeId nodeId_{};
  std::size_t colorIndex_{};
};

HasPathTask::HasPathTask(const Graph& graph, const ColorList& colorList,
                         Shared<VisitedNodes> visitedNodes, NodeId nodeId,
                         ColorIndex colorIndex)
    : graph_(&graph),
      colorList_(&colorList),
      visitedNodes_(visitedNodes),
      nodeId_(nodeId),
      colorIndex_(colorIndex) {
  assert(graph_ != nullptr);
  assert(colorList_ != nullptr);
}

bool HasPathTask::operator<(const HasPathTask& other) const {
  return colorIndex_ < other.colorIndex_;
}

auto HasPathTask::start(const Graph& graph, const ColorList& colorList,
                        Queue<HasPathTask>* taskQueue) -> Status {
  if (colorList.empty()) return Status::FAIL;

  auto firstColor = colorList.front();
  auto nodeIds = graph.findNodesByColor(firstColor);
  if (nodeIds.empty()) return Status::FAIL;
  if (colorList.size() == 1) return Status::SUCCESS;

  auto visitedNodes = std::make_shared<VisitedNodes>();

  for (auto nodeId : nodeIds) {
    constexpr auto FIRST_COLOR_INDEX = std::size_t(0);
    visitedNodes->emplace(nodeId, FIRST_COLOR_INDEX);
    taskQueue->emplace(graph, colorList, visitedNodes, nodeId,
                       FIRST_COLOR_INDEX + 1);
  }

  return Status::CONTINUE;
}

auto HasPathTask::execute(Queue<HasPathTask>* taskQueue) const -> Status {
  auto nextColor = colorList_->at(colorIndex_);
  const auto& nodesWithNextColor = graph_->findNodesByColor(nextColor);
  if (nodesWithNextColor.empty()) {
    return Status::CONTINUE;
  }

  for (auto nextNodeId : graph_->findNodesBySource(nodeId_)) {
    auto taskId = std::make_tuple(nextNodeId, colorIndex_);
    auto [_, firstVisit] = visitedNodes_->emplace(taskId);
    if (!firstVisit) {
      continue;
    }

    if (nodesWithNextColor.count(nextNodeId)) {
      auto nextColorIndex = colorIndex_ + 1;
      if (nextColorIndex == colorList_->size()) {
        return Status::SUCCESS;
      }
      taskQueue->emplace(*graph_, *colorList_, visitedNodes_, nextNodeId,
                         nextColorIndex);
    } else {
      taskQueue->emplace(*graph_, *colorList_, visitedNodes_, nextNodeId,
                         colorIndex_);
    }
  }

  return Status::CONTINUE;
}

}  // namespace

bool hasPath(const Graph& graph, const ColorList& colorList) {
  using Status = HasPathTask::Status;

  auto taskQueue = Queue<HasPathTask>();
  auto status = HasPathTask::start(graph, colorList, &taskQueue);
  while (status == Status::CONTINUE  //
         && !taskQueue.empty()) {
    auto task = std::move(taskQueue.top());
    taskQueue.pop();
    status = task.execute(&taskQueue);
  }

  return bool(status == Status::SUCCESS);
}

}  // namespace graph
