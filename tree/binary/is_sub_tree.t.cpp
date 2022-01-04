
#include <gtest/gtest.h>

#include "is_sub_tree.h"


namespace tree::binary {

class TestIsSubTree : public ::testing::Test {
 protected:
  void runTest(std::size_t numValues);

 private:
  auto createBinaryTree(std::size_t numValues) -> Ptr<BinaryTreeNode>;
};

TEST_F(TestIsSubTree, testIsSubTree_depth1) { runTest(1); }
TEST_F(TestIsSubTree, testIsSubTree_depth2) { runTest(3); }
TEST_F(TestIsSubTree, testIsSubTree_depth3) { runTest(7); }
TEST_F(TestIsSubTree, testIsSubTree_depth4) { runTest(15); }
TEST_F(TestIsSubTree, testIsSubTree_depth5) { runTest(31); }

void TestIsSubTree::runTest(std::size_t numNodes) {
  auto tree = createBinaryTree(numNodes);
  ASSERT_TRUE(tree);

  EXPECT_TRUE(isSubTree(*tree, *tree));
  EXPECT_TRUE(isSubTree(*tree, *binary::createBinaryTree({"a"})));

  if (numNodes >= 3) {
    EXPECT_TRUE(isSubTree(*tree, *binary::createBinaryTree({"a", "b", "c"})));
  }

  if (numNodes >= 7) {
    EXPECT_FALSE(isSubTree(*tree, *binary::createBinaryTree({"b", "d", "f"})));
    EXPECT_TRUE(isSubTree(*tree, *binary::createBinaryTree({"e", "f", "g"})));
    EXPECT_FALSE(isSubTree(*tree, *binary::createBinaryTree({"b", "c", "d"})));
    EXPECT_FALSE(isSubTree(*binary::createBinaryTree({"a", "b", "c"}), *tree));
  }
}

auto TestIsSubTree::createBinaryTree(std::size_t numValues)
    -> Ptr<BinaryTreeNode> {
  auto inputValues = std::vector<std::string>();
  for (auto i = std::size_t(); i < numValues; i++) {
    auto nodeName = std::string("a");
    nodeName.back() += i;
    inputValues.emplace_back(nodeName);
  }

  return binary::createBinaryTree(inputValues);
}

}  // namespace tree::binary
