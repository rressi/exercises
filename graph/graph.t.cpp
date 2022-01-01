
#include <gtest/gtest.h>

#include "graph.h"

namespace graph {
namespace {

using NodeId = graph::Graph::NodeId;
using Edges = std::vector<NodeId>;

struct WithNode {
    Color color{};
    Edges edges{};
};
using WithGraph = std::vector<WithNode>;
using ExpectedResult = bool;

struct GraphTest_TestCase {
    WithGraph withGraph{};
    ColorList colorList{};
    ExpectedResult expectedResult{};
};

}  // namespace

class TestGraph : public ::testing::TestWithParam<GraphTest_TestCase> {
   public:
    using TestCase = GraphTest_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
        -> std::string;
};

INSTANTIATE_TEST_SUITE_P(
    ZeroItems, TestGraph,
    testing::Values(

        TestGraph::TestCase{WithGraph{}, ColorList{}, ExpectedResult{false}},
        TestGraph::TestCase{WithGraph{}, ColorList{Color::Red, Color::Green},
                            ExpectedResult{false}}

        ),
    &TestGraph::getTestName);

INSTANTIATE_TEST_SUITE_P(
    OneItem, TestGraph,
    testing::Values(

        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{0}}},
                            ColorList{Color::Red}, ExpectedResult{true}},
        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{}}},
                            ColorList{Color::Red}, ExpectedResult{true}},
        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{0}}},
                            ColorList{Color::Yellow}, ExpectedResult{false}},
        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{0}}},
                            ColorList{Color::Red, Color::Yellow},
                            ExpectedResult{false}}

        ),
    &TestGraph::getTestName);

INSTANTIATE_TEST_SUITE_P(
    TwoItems, TestGraph,
    testing::Values(

        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Red}, ExpectedResult{true}},
        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Red, Color::Yellow},
                            ExpectedResult{true}},
        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Yellow, Color::Red},
                            ExpectedResult{true}},
        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{0}},
                                      WithNode{Color::Yellow, Edges{1}}},
                            ColorList{Color::Yellow, Color::Red},
                            ExpectedResult{false}},
        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{0}},
                                      WithNode{Color::Yellow, Edges{}}},
                            ColorList{Color::Yellow, Color::Red},
                            ExpectedResult{false}},
        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{0}},
                                      WithNode{Color::Yellow, Edges{1}}},
                            ColorList{Color::Yellow}, ExpectedResult{true}}

        ),
    &TestGraph::getTestName);

INSTANTIATE_TEST_SUITE_P(
    ThreeItems, TestGraph,
    testing::Values(

        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Green, Edges{2}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Red}, ExpectedResult{true}},
        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Green, Edges{2}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Red, Color::Green},
                            ExpectedResult{true}},
        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Green, Edges{2}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Green, Color::Yellow},
                            ExpectedResult{true}},
        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Green, Edges{2}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Yellow, Color::Red},
                            ExpectedResult{true}},
        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Green, Edges{2}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Yellow, Color::Red, Color::Green},
                            ExpectedResult{true}},
        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Green, Edges{2}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Red, Color::Yellow},
                            ExpectedResult{true}},
        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{}},
                                      WithNode{Color::Green, Edges{2}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Red, Color::Yellow},
                            ExpectedResult{false}}

        ),
    &TestGraph::getTestName);

INSTANTIATE_TEST_SUITE_P(
    BigGraph, TestGraph,
    testing::Values(

        TestGraph::TestCase{
            WithGraph{
                WithNode{Color::Red, Edges{1}}, WithNode{Color::Red, Edges{2}},
                WithNode{Color::Red, Edges{3}}, WithNode{Color::Red, Edges{4}},
                WithNode{Color::Red, Edges{5}}, WithNode{Color::Red, Edges{}}},
            ColorList{Color::Red, Color::Red, Color::Red},
            ExpectedResult{true}},

        TestGraph::TestCase{
            WithGraph{WithNode{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                      WithNode{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                      WithNode{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                      WithNode{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                      WithNode{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                      WithNode{Color::Red, Edges{0, 1, 2, 3, 4, 5}}},
            ColorList{Color::Red, Color::Red, Color::Red},
            ExpectedResult{true}},

        TestGraph::TestCase{
            WithGraph{WithNode{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                      WithNode{Color::Green, Edges{0, 1, 2, 3, 4, 5}},
                      WithNode{Color::Orange, Edges{0, 1, 2, 3, 4, 5}},
                      WithNode{Color::Yellow, Edges{0, 1, 2, 3, 4, 5}},
                      WithNode{Color::Blue, Edges{0, 1, 2, 3, 4, 5}},
                      WithNode{Color::White, Edges{0, 1, 2, 3, 4, 5}}},
            ColorList{Color::Red, Color::Yellow, Color::White},
            ExpectedResult{true}},

        TestGraph::TestCase{
            WithGraph{WithNode{Color::Red, Edges{0, 1, 2, 3}},
                      WithNode{Color::Green, Edges{0, 1, 2, 3}},
                      WithNode{Color::Orange, Edges{0, 1, 2, 3}},
                      WithNode{Color::Yellow, Edges{0, 1, 2, 3}},
                      WithNode{Color::Blue, Edges{0, 1, 2, 3, 4, 5}},
                      WithNode{Color::White, Edges{0, 1, 2, 3, 4, 5}}},
            ColorList{Color::Red, Color::Yellow, Color::White},
            ExpectedResult{false}},

        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Green, Edges{2}},
                                      WithNode{Color::Orange, Edges{3}},
                                      WithNode{Color::Yellow, Edges{4}},
                                      WithNode{Color::Blue, Edges{5}},
                                      WithNode{Color::White, Edges{}}},
                            ColorList{Color::Red, Color::White},
                            ExpectedResult{true}},

        TestGraph::TestCase{WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Green, Edges{2}},
                                      WithNode{Color::Orange, Edges{3}},
                                      WithNode{Color::Yellow, Edges{4}},
                                      WithNode{Color::Blue, Edges{5}},
                                      WithNode{Color::White, Edges{}}},
                            ColorList{Color::Red, Color::White, Color::Orange},
                            ExpectedResult{false}}

        ),
    &TestGraph::getTestName);

TEST_P(TestGraph, testHasPath) {
    const auto &testCase = GetParam();

    auto graph = Graph();
    for (const auto &withNode : testCase.withGraph) {
        graph.addNode(withNode.color);
    }
    auto sourceNodeId = Graph::NodeId();
    for (const auto &withNode : testCase.withGraph) {
        for (const auto &destinationNodeId : withNode.edges) {
            graph.addEdge(sourceNodeId, destinationNodeId);
        }
        sourceNodeId++;
    }

    EXPECT_EQ(testCase.expectedResult, graph.hasPath(testCase.colorList));
}

auto TestGraph::getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
    -> std::string {
    const auto &testCase = testInfo.param;
    auto buffer = std::string();
    auto separator = "";

    for (const auto &withNode : testCase.withGraph) {
        buffer.append(separator + toString(withNode.color) + "Node");
        for (auto nodeId : withNode.edges) {
            buffer.append(std::to_string(nodeId));
        }
        separator = "_";
    }

    buffer.append("_path");
    for (auto color : testCase.colorList) {
        buffer.append(toString(color));
    }

    return buffer;
}

}  // namespace graph
