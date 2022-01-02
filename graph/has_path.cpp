
#include "has_path.h"

namespace graph {

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

auto HasPathTask::start(const Graph& graph, const ColorList& colorList,
                        Queue<HasPathTask>* taskQueue) -> Status {
    if (colorList.empty()) return Status::FAIL;

    auto firstColor = colorList.front();
    auto nodeIds = graph.nodesWithColor(firstColor);
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
    const auto& nodesWithNextColor = graph_->nodesWithColor(nextColor);
    if (nodesWithNextColor.empty()) {
        return Status::CONTINUE;
    }

    for (auto nextNodeId : graph_->nodesFromNode(nodeId_)) {
        auto taskId = std::make_tuple(nextNodeId, colorIndex_);
        auto [_, newInsertion] = visitedNodes_->emplace(taskId);
        if (!newInsertion) {
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

}  // namespace graph
