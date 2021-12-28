
#include <gtest/gtest.h>

#include "graph.h"

namespace graph {

TEST(GraphTest, empty) {
    EXPECT_FALSE(has_path(Graph{}, ColorList{}));
    EXPECT_FALSE(has_path(Graph{}, ColorList{Color::Red, Color::Green}));
}

TEST(GraphTest, oneItem) {
    EXPECT_TRUE(has_path(Graph{Node{.color = Color::Red, .edges = Edges{0}}},
                         ColorList{Color::Red}));
    EXPECT_TRUE(has_path(Graph{Node{.color = Color::Red, .edges = Edges{}}},
                         ColorList{Color::Red}));
    EXPECT_FALSE(has_path(Graph{Node{.color = Color::Red, .edges = Edges{0}}},
                          ColorList{Color::Yellow}));
    EXPECT_FALSE(has_path(Graph{Node{.color = Color::Red, .edges = Edges{0}}},
                          ColorList{Color::Red, Color::Yellow}));
}

TEST(GraphTest, twoItems) {
    EXPECT_TRUE(has_path(Graph{Node{.color = Color::Red, .edges = {1}},
                               Node{.color = Color::Yellow, .edges = {0}}},
                         ColorList{Color::Red}));
    EXPECT_TRUE(has_path(Graph{Node{.color = Color::Red, .edges = {1}},
                               Node{.color = Color::Yellow, .edges = {0}}},
                         ColorList{Color::Red, Color::Yellow}));
    EXPECT_TRUE(has_path(Graph{Node{.color = Color::Red, .edges = {1}},
                               Node{.color = Color::Yellow, .edges = {0}}},
                         ColorList{Color::Yellow, Color::Red}));
    EXPECT_FALSE(has_path(Graph{Node{.color = Color::Red, .edges = {0}},
                                Node{.color = Color::Yellow, .edges = {1}}},
                          ColorList{Color::Yellow, Color::Red}));
    EXPECT_FALSE(has_path(Graph{Node{.color = Color::Red, .edges = {0}},
                                Node{.color = Color::Yellow, .edges = {}}},
                          ColorList{Color::Yellow, Color::Red}));
    EXPECT_TRUE(has_path(Graph{Node{.color = Color::Red, .edges = {0}},
                               Node{.color = Color::Yellow, .edges = {1}}},
                         ColorList{Color::Yellow}));
}

TEST(GraphTest, threeItems) {
    EXPECT_TRUE(has_path(Graph{Node{.color = Color::Red, .edges = {1}},
                               Node{.color = Color::Green, .edges = {2}},
                               Node{.color = Color::Yellow, .edges = {0}}},
                         ColorList{Color::Red}));
    EXPECT_TRUE(has_path(Graph{Node{.color = Color::Red, .edges = {1}},
                               Node{.color = Color::Green, .edges = {2}},
                               Node{.color = Color::Yellow, .edges = {0}}},
                         ColorList{Color::Red, Color::Green}));
    EXPECT_TRUE(has_path(Graph{Node{.color = Color::Red, .edges = {1}},
                               Node{.color = Color::Green, .edges = {2}},
                               Node{.color = Color::Yellow, .edges = {0}}},
                         ColorList{Color::Green, Color::Yellow}));
    EXPECT_TRUE(has_path(Graph{Node{.color = Color::Red, .edges = {1}},
                               Node{.color = Color::Green, .edges = {2}},
                               Node{.color = Color::Yellow, .edges = {0}}},
                         ColorList{Color::Yellow, Color::Red}));
    EXPECT_TRUE(has_path(Graph{Node{.color = Color::Red, .edges = {1}},
                               Node{.color = Color::Green, .edges = {2}},
                               Node{.color = Color::Yellow, .edges = {0}}},
                         ColorList{Color::Yellow, Color::Red, Color::Green}));
    EXPECT_TRUE(has_path(Graph{Node{.color = Color::Red, .edges = {1}},
                               Node{.color = Color::Green, .edges = {2}},
                               Node{.color = Color::Yellow, .edges = {0}}},
                         ColorList{Color::Red, Color::Yellow}));
    EXPECT_FALSE(has_path(Graph{Node{.color = Color::Red, .edges = {}},
                                Node{.color = Color::Green, .edges = {2}},
                                Node{.color = Color::Yellow, .edges = {0}}},
                          ColorList{Color::Red, Color::Yellow}));
}

TEST(GraphTest, bigGraph) {
    EXPECT_TRUE(has_path(Graph{Node{.color = Color::Red, .edges = {1}},
                               Node{.color = Color::Red, .edges = {2}},
                               Node{.color = Color::Red, .edges = {3}},
                               Node{.color = Color::Red, .edges = {4}},
                               Node{.color = Color::Red, .edges = {5}},
                               Node{.color = Color::Red, .edges = {}}},
                         ColorList{Color::Red, Color::Red, Color::Red}));
    EXPECT_TRUE(
        has_path(Graph{Node{.color = Color::Red, .edges = {0, 1, 2, 3, 4, 5}},
                       Node{.color = Color::Red, .edges = {0, 1, 2, 3, 4, 5}},
                       Node{.color = Color::Red, .edges = {0, 1, 2, 3, 4, 5}},
                       Node{.color = Color::Red, .edges = {0, 1, 2, 3, 4, 5}},
                       Node{.color = Color::Red, .edges = {0, 1, 2, 3, 4, 5}},
                       Node{.color = Color::Red, .edges = {0, 1, 2, 3, 4, 5}}},
                 ColorList{Color::Red, Color::Red, Color::Red}));
    EXPECT_TRUE(has_path(
        Graph{Node{.color = Color::Red, .edges = {0, 1, 2, 3, 4, 5}},
              Node{.color = Color::Green, .edges = {0, 1, 2, 3, 4, 5}},
              Node{.color = Color::Orange, .edges = {0, 1, 2, 3, 4, 5}},
              Node{.color = Color::Yellow, .edges = {0, 1, 2, 3, 4, 5}},
              Node{.color = Color::Blue, .edges = {0, 1, 2, 3, 4, 5}},
              Node{.color = Color::White, .edges = {0, 1, 2, 3, 4, 5}}},
        ColorList{Color::Red, Color::Yellow, Color::White}));

    EXPECT_FALSE(has_path(
        Graph{Node{.color = Color::Red, .edges = {0, 1, 2, 3}},
              Node{.color = Color::Green, .edges = {0, 1, 2, 3}},
              Node{.color = Color::Orange, .edges = {0, 1, 2, 3}},
              Node{.color = Color::Yellow, .edges = {0, 1, 2, 3}},
              Node{.color = Color::Blue, .edges = {0, 1, 2, 3, 4, 5}},
              Node{.color = Color::White, .edges = {0, 1, 2, 3, 4, 5}}},
        ColorList{Color::Red, Color::Yellow, Color::White}));

    EXPECT_TRUE(has_path(Graph{Node{.color = Color::Red, .edges = {1}},
                               Node{.color = Color::Green, .edges = {2}},
                               Node{.color = Color::Orange, .edges = {3}},
                               Node{.color = Color::Yellow, .edges = {4}},
                               Node{.color = Color::Blue, .edges = {5}},
                               Node{.color = Color::White, .edges = {}}},
                         ColorList{Color::Red, Color::White}));

    EXPECT_FALSE(has_path(Graph{Node{.color = Color::Red, .edges = {1}},
                                Node{.color = Color::Green, .edges = {2}},
                                Node{.color = Color::Orange, .edges = {3}},
                                Node{.color = Color::Yellow, .edges = {4}},
                                Node{.color = Color::Blue, .edges = {5}},
                                Node{.color = Color::White, .edges = {}}},
                          ColorList{Color::Red, Color::White, Color::Orange}));
}

}  // namespace graph
