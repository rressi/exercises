
#include <gtest/gtest.h>

#include "graph.h"


namespace graph {
namespace test {
namespace {

using Color = graph::Graph::Color;
using ColorList = graph::Graph::ColorList;
using NodeId = graph::Graph::NodeId;
using Edges = std::vector<NodeId>;

struct WithNode {
    Color color{};
    Edges edges{};
};
using WithGraph = std::vector<WithNode>;

bool testHasPath(const WithGraph &withGraph, const ColorList &colorList) {
    auto graph = Graph();
    for (const auto &withNode : withGraph) {
        graph.addNode(withNode.color);
    }
    auto sourceNodeId = Graph::NodeId();
    for (const auto &withNode : withGraph) {
        for (const auto &destinationNodeId : withNode.edges) {
            graph.addEdge(sourceNodeId, destinationNodeId);
        }
        sourceNodeId++;
    }

    return graph.hasPath(colorList);
}

}  // namespace

TEST(GraphTest, empty) {
    EXPECT_FALSE(testHasPath(WithGraph{}, ColorList{}));
    EXPECT_FALSE(testHasPath(WithGraph{}, ColorList{Color::Red, Color::Green}));
}

TEST(GraphTest, oneItem) {
    EXPECT_TRUE(testHasPath(WithGraph{WithNode{Color::Red, Edges{0}}},
                            ColorList{Color::Red}));
    EXPECT_TRUE(testHasPath(WithGraph{WithNode{Color::Red, Edges{}}},
                            ColorList{Color::Red}));
    EXPECT_FALSE(testHasPath(WithGraph{WithNode{Color::Red, Edges{0}}},
                             ColorList{Color::Yellow}));
    EXPECT_FALSE(testHasPath(WithGraph{WithNode{Color::Red, Edges{0}}},
                             ColorList{Color::Red, Color::Yellow}));
}

TEST(GraphTest, twoItems) {
    EXPECT_TRUE(testHasPath(WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Red}));
    EXPECT_TRUE(testHasPath(WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Red, Color::Yellow}));
    EXPECT_TRUE(testHasPath(WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Yellow, Color::Red}));
    EXPECT_FALSE(testHasPath(WithGraph{WithNode{Color::Red, Edges{0}},
                                       WithNode{Color::Yellow, Edges{1}}},
                             ColorList{Color::Yellow, Color::Red}));
    EXPECT_FALSE(testHasPath(WithGraph{WithNode{Color::Red, Edges{0}},
                                       WithNode{Color::Yellow, Edges{}}},
                             ColorList{Color::Yellow, Color::Red}));
    EXPECT_TRUE(testHasPath(WithGraph{WithNode{Color::Red, Edges{0}},
                                      WithNode{Color::Yellow, Edges{1}}},
                            ColorList{Color::Yellow}));
}

TEST(GraphTest, threeItems) {
    EXPECT_TRUE(testHasPath(WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Green, Edges{2}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Red}));
    EXPECT_TRUE(testHasPath(WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Green, Edges{2}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Red, Color::Green}));
    EXPECT_TRUE(testHasPath(WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Green, Edges{2}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Green, Color::Yellow}));
    EXPECT_TRUE(testHasPath(WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Green, Edges{2}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Yellow, Color::Red}));
    EXPECT_TRUE(
        testHasPath(WithGraph{WithNode{Color::Red, Edges{1}},
                              WithNode{Color::Green, Edges{2}},
                              WithNode{Color::Yellow, Edges{0}}},
                    ColorList{Color::Yellow, Color::Red, Color::Green}));
    EXPECT_TRUE(testHasPath(WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Green, Edges{2}},
                                      WithNode{Color::Yellow, Edges{0}}},
                            ColorList{Color::Red, Color::Yellow}));
    EXPECT_FALSE(testHasPath(WithGraph{WithNode{Color::Red, Edges{}},
                                       WithNode{Color::Green, Edges{2}},
                                       WithNode{Color::Yellow, Edges{0}}},
                             ColorList{Color::Red, Color::Yellow}));
}

TEST(GraphTest, bigGraph) {
    EXPECT_TRUE(testHasPath(
        WithGraph{
            WithNode{Color::Red, Edges{1}}, WithNode{Color::Red, Edges{2}},
            WithNode{Color::Red, Edges{3}}, WithNode{Color::Red, Edges{4}},
            WithNode{Color::Red, Edges{5}}, WithNode{Color::Red, Edges{}}},
        ColorList{Color::Red, Color::Red, Color::Red}));
    EXPECT_TRUE(
        testHasPath(WithGraph{WithNode{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                              WithNode{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                              WithNode{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                              WithNode{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                              WithNode{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                              WithNode{Color::Red, Edges{0, 1, 2, 3, 4, 5}}},
                    ColorList{Color::Red, Color::Red, Color::Red}));
    EXPECT_TRUE(
        testHasPath(WithGraph{WithNode{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                              WithNode{Color::Green, Edges{0, 1, 2, 3, 4, 5}},
                              WithNode{Color::Orange, Edges{0, 1, 2, 3, 4, 5}},
                              WithNode{Color::Yellow, Edges{0, 1, 2, 3, 4, 5}},
                              WithNode{Color::Blue, Edges{0, 1, 2, 3, 4, 5}},
                              WithNode{Color::White, Edges{0, 1, 2, 3, 4, 5}}},
                    ColorList{Color::Red, Color::Yellow, Color::White}));
    EXPECT_FALSE(
        testHasPath(WithGraph{WithNode{Color::Red, Edges{0, 1, 2, 3}},
                              WithNode{Color::Green, Edges{0, 1, 2, 3}},
                              WithNode{Color::Orange, Edges{0, 1, 2, 3}},
                              WithNode{Color::Yellow, Edges{0, 1, 2, 3}},
                              WithNode{Color::Blue, Edges{0, 1, 2, 3, 4, 5}},
                              WithNode{Color::White, Edges{0, 1, 2, 3, 4, 5}}},
                    ColorList{Color::Red, Color::Yellow, Color::White}));
    EXPECT_TRUE(testHasPath(WithGraph{WithNode{Color::Red, Edges{1}},
                                      WithNode{Color::Green, Edges{2}},
                                      WithNode{Color::Orange, Edges{3}},
                                      WithNode{Color::Yellow, Edges{4}},
                                      WithNode{Color::Blue, Edges{5}},
                                      WithNode{Color::White, Edges{}}},
                            ColorList{Color::Red, Color::White}));
    EXPECT_FALSE(testHasPath(
        WithGraph{
            WithNode{Color::Red, Edges{1}}, WithNode{Color::Green, Edges{2}},
            WithNode{Color::Orange, Edges{3}},
            WithNode{Color::Yellow, Edges{4}}, WithNode{Color::Blue, Edges{5}},
            WithNode{Color::White, Edges{}}},
        ColorList{Color::Red, Color::White, Color::Orange}));
}

}  // namespace test
}  // namespace graph
