#include "graph.h"

#include <algorithm>
#include <deque>
#include <set>


namespace graph {

using ColorQueue = std::deque<Color>;
using EdgeQueue = std::deque<Edge>;
using VisitedSet = std::set<Edge>;

struct Runner {
    ColorQueue colorQueue{};
    EdgeQueue edgeQueue{};
    VisitedSet visitedSet{};
};

bool has_path(const Graph &graph, const ColorList &colorList) {
    if (colorList.empty()) {
        return false;
    }

    auto firstColor = colorList.front();
    if (colorList.size() == 1) {
        auto findIt = std::find_if(graph.begin(), graph.end(),
                                   [firstColor](const Node &node) {
                                       return node.color == firstColor;
                                   });
        return findIt != graph.end();
    }

    auto runners = std::vector<Runner>();
    for (auto edge = Edge(0); edge < graph.size(); edge++) {
        const auto &node = graph.at(edge);
        if (node.color != firstColor) continue;
        if (node.edges.empty()) continue;

        runners.emplace_back(
            Runner{ColorQueue{colorList.begin() + 1, colorList.end()},  //
                   EdgeQueue{node.edges.begin(), node.edges.end()},     //
                   VisitedSet{edge}});
    }

    while (!runners.empty()) {
        for (auto &runner : runners) {
            auto edge = runner.edgeQueue.front();
            runner.edgeQueue.pop_front();

            auto targetColor = runner.colorQueue.front();

            const auto &node = graph.at(edge);
            if (node.color == targetColor) {
                runner.colorQueue.pop_front();
                if (runner.colorQueue.empty()) {
                    return true;
                }
            }

            runner.visitedSet.insert(edge);
            for (auto nextEdge : node.edges) {
                if (runner.visitedSet.count(nextEdge) == 0) {
                    runner.edgeQueue.push_back(nextEdge);
                }
            }
        }

        auto it = std::remove_if(
            runners.begin(), runners.end(),
            [](const Runner &runner) { return runner.edgeQueue.empty(); });
        runners.resize(std::distance(runners.begin(), it));
    }

    return false;
}

}  // namespace graph
