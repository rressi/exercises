
#include <gtest/gtest.h>

#include "graph.h"

namespace graph {

TEST(GraphTest, empty) {
    EXPECT_FALSE(has_path(Graph{}, ColorList{}));
    EXPECT_FALSE(has_path(Graph{}, ColorList{Color::Red, Color::Green}));
}

TEST(GraphTest, oneItem) {
    EXPECT_TRUE(
        has_path(Graph{Node{Color::Red, Edges{0}}}, ColorList{Color::Red}));
    EXPECT_TRUE(
        has_path(Graph{Node{Color::Red, Edges{}}}, ColorList{Color::Red}));
    EXPECT_FALSE(
        has_path(Graph{Node{Color::Red, Edges{0}}}, ColorList{Color::Yellow}));
    EXPECT_FALSE(has_path(Graph{Node{Color::Red, Edges{0}}},
                          ColorList{Color::Red, Color::Yellow}));
}

TEST(GraphTest, twoItems) {
    EXPECT_TRUE(has_path(
        Graph{Node{Color::Red, Edges{1}}, Node{Color::Yellow, Edges{0}}},
        ColorList{Color::Red}));
    EXPECT_TRUE(has_path(
        Graph{Node{Color::Red, Edges{1}}, Node{Color::Yellow, Edges{0}}},
        ColorList{Color::Red, Color::Yellow}));
    EXPECT_TRUE(has_path(
        Graph{Node{Color::Red, Edges{1}}, Node{Color::Yellow, Edges{0}}},
        ColorList{Color::Yellow, Color::Red}));
    EXPECT_FALSE(has_path(
        Graph{Node{Color::Red, Edges{0}}, Node{Color::Yellow, Edges{1}}},
        ColorList{Color::Yellow, Color::Red}));
    EXPECT_FALSE(has_path(
        Graph{Node{Color::Red, Edges{0}}, Node{Color::Yellow, Edges{}}},
        ColorList{Color::Yellow, Color::Red}));
    EXPECT_TRUE(has_path(
        Graph{Node{Color::Red, Edges{0}}, Node{Color::Yellow, Edges{1}}},
        ColorList{Color::Yellow}));
}

TEST(GraphTest, threeItems) {
    EXPECT_TRUE(
        has_path(Graph{Node{Color::Red, Edges{1}}, Node{Color::Green, Edges{2}},
                       Node{Color::Yellow, Edges{0}}},
                 ColorList{Color::Red}));
    EXPECT_TRUE(
        has_path(Graph{Node{Color::Red, Edges{1}}, Node{Color::Green, Edges{2}},
                       Node{Color::Yellow, Edges{0}}},
                 ColorList{Color::Red, Color::Green}));
    EXPECT_TRUE(
        has_path(Graph{Node{Color::Red, Edges{1}}, Node{Color::Green, Edges{2}},
                       Node{Color::Yellow, Edges{0}}},
                 ColorList{Color::Green, Color::Yellow}));
    EXPECT_TRUE(
        has_path(Graph{Node{Color::Red, Edges{1}}, Node{Color::Green, Edges{2}},
                       Node{Color::Yellow, Edges{0}}},
                 ColorList{Color::Yellow, Color::Red}));
    EXPECT_TRUE(
        has_path(Graph{Node{Color::Red, Edges{1}}, Node{Color::Green, Edges{2}},
                       Node{Color::Yellow, Edges{0}}},
                 ColorList{Color::Yellow, Color::Red, Color::Green}));
    EXPECT_TRUE(
        has_path(Graph{Node{Color::Red, Edges{1}}, Node{Color::Green, Edges{2}},
                       Node{Color::Yellow, Edges{0}}},
                 ColorList{Color::Red, Color::Yellow}));
    EXPECT_FALSE(
        has_path(Graph{Node{Color::Red, Edges{}}, Node{Color::Green, Edges{2}},
                       Node{Color::Yellow, Edges{0}}},
                 ColorList{Color::Red, Color::Yellow}));
}

TEST(GraphTest, bigGraph) {
    EXPECT_TRUE(
        has_path(Graph{Node{Color::Red, Edges{1}}, Node{Color::Red, Edges{2}},
                       Node{Color::Red, Edges{3}}, Node{Color::Red, Edges{4}},
                       Node{Color::Red, Edges{5}}, Node{Color::Red, Edges{}}},
                 ColorList{Color::Red, Color::Red, Color::Red}));
    EXPECT_TRUE(has_path(Graph{Node{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                               Node{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                               Node{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                               Node{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                               Node{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                               Node{Color::Red, Edges{0, 1, 2, 3, 4, 5}}},
                         ColorList{Color::Red, Color::Red, Color::Red}));
    EXPECT_TRUE(has_path(Graph{Node{Color::Red, Edges{0, 1, 2, 3, 4, 5}},
                               Node{Color::Green, Edges{0, 1, 2, 3, 4, 5}},
                               Node{Color::Orange, Edges{0, 1, 2, 3, 4, 5}},
                               Node{Color::Yellow, Edges{0, 1, 2, 3, 4, 5}},
                               Node{Color::Blue, Edges{0, 1, 2, 3, 4, 5}},
                               Node{Color::White, Edges{0, 1, 2, 3, 4, 5}}},
                         ColorList{Color::Red, Color::Yellow, Color::White}));

    EXPECT_FALSE(has_path(Graph{Node{Color::Red, Edges{0, 1, 2, 3}},
                                Node{Color::Green, Edges{0, 1, 2, 3}},
                                Node{Color::Orange, Edges{0, 1, 2, 3}},
                                Node{Color::Yellow, Edges{0, 1, 2, 3}},
                                Node{Color::Blue, Edges{0, 1, 2, 3, 4, 5}},
                                Node{Color::White, Edges{0, 1, 2, 3, 4, 5}}},
                          ColorList{Color::Red, Color::Yellow, Color::White}));

    EXPECT_TRUE(has_path(
        Graph{Node{Color::Red, Edges{1}}, Node{Color::Green, Edges{2}},
              Node{Color::Orange, Edges{3}}, Node{Color::Yellow, Edges{4}},
              Node{Color::Blue, Edges{5}}, Node{Color::White, Edges{}}},
        ColorList{Color::Red, Color::White}));

    EXPECT_FALSE(has_path(
        Graph{Node{Color::Red, Edges{1}}, Node{Color::Green, Edges{2}},
              Node{Color::Orange, Edges{3}}, Node{Color::Yellow, Edges{4}},
              Node{Color::Blue, Edges{5}}, Node{Color::White, Edges{}}},
        ColorList{Color::Red, Color::White, Color::Orange}));
}

}  // namespace graph
