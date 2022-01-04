
#include <gtest/gtest.h>

#include "binary_tree.h"


namespace tree::binary {

class TestBinaryTree : public ::testing::Test {};

TEST_F(TestBinaryTree, testCreateBinaryTree_evenNumItems) {
  auto tree = createBinaryTree({"a", "b", "c", "d", "e", "f"});

  ASSERT_TRUE(tree);
  EXPECT_EQ("d", tree->value);

  ASSERT_TRUE(tree->left);
  EXPECT_EQ("b", tree->left->value);

  ASSERT_TRUE(tree->right);
  EXPECT_EQ("f", tree->right->value);

  ASSERT_TRUE(tree->left->left);
  EXPECT_EQ("a", tree->left->left->value);

  ASSERT_TRUE(tree->left->right);
  EXPECT_EQ("c", tree->left->right->value);

  ASSERT_TRUE(tree->right->left);
  EXPECT_EQ("e", tree->right->left->value);

  ASSERT_FALSE(tree->right->right);

  ASSERT_FALSE(tree->left->left->left);
  ASSERT_FALSE(tree->left->left->right);
  ASSERT_FALSE(tree->left->right->left);
  ASSERT_FALSE(tree->left->right->right);
  ASSERT_FALSE(tree->right->left->left);
  ASSERT_FALSE(tree->right->left->right);
}

TEST_F(TestBinaryTree, testCreateBinaryTree_oddNumItems) {
  auto tree = createBinaryTree({"a", "b", "c", "d", "e", "f", "g"});

  ASSERT_TRUE(tree);
  EXPECT_EQ("d", tree->value);

  ASSERT_TRUE(tree->left);
  EXPECT_EQ("b", tree->left->value);

  ASSERT_TRUE(tree->right);
  EXPECT_EQ("f", tree->right->value);

  ASSERT_TRUE(tree->left->left);
  EXPECT_EQ("a", tree->left->left->value);

  ASSERT_TRUE(tree->left->right);
  EXPECT_EQ("c", tree->left->right->value);

  ASSERT_TRUE(tree->right->left);
  EXPECT_EQ("e", tree->right->left->value);

  ASSERT_TRUE(tree->right->right);
  EXPECT_EQ("g", tree->right->right->value);

  EXPECT_FALSE(tree->left->left->left);
  EXPECT_FALSE(tree->left->left->right);
  EXPECT_FALSE(tree->left->right->left);
  EXPECT_FALSE(tree->left->right->right);
  EXPECT_FALSE(tree->right->left->left);
  EXPECT_FALSE(tree->right->left->right);
  EXPECT_FALSE(tree->right->right->left);
  EXPECT_FALSE(tree->right->right->right);
}

TEST_F(TestBinaryTree, testCreateBinaryTree_singleton) {
  auto tree = createBinaryTree({"a"});

  ASSERT_TRUE(tree);
  EXPECT_EQ("a", tree->value);
  EXPECT_FALSE(tree->left);
  EXPECT_FALSE(tree->right);
}

TEST_F(TestBinaryTree, testCreateBinaryTree_void) {
  auto tree = createBinaryTree({});
  ASSERT_FALSE(tree);
}

TEST_F(TestBinaryTree, testIsBinarySearchTree) {
  EXPECT_TRUE(isBinarySearchTree(createBinaryTree({})));
  EXPECT_TRUE(isBinarySearchTree(createBinaryTree({"z"})));
  EXPECT_TRUE(isBinarySearchTree(
      createBinaryTree({"a", "b", "c", "d", "e", "f", "g"})));
  EXPECT_TRUE(isBinarySearchTree(
      createBinaryTree({"b", "b", "b", "b", "b", "b", "b"})));
  EXPECT_TRUE(isBinarySearchTree(
      createBinaryTree({"a", "c", "c", "d", "d", "f", "f", "g"})));

  EXPECT_FALSE(isBinarySearchTree(createBinaryTree({"b", "a"})));
  EXPECT_FALSE(isBinarySearchTree(createBinaryTree({"a", "b", "a"})));
  EXPECT_FALSE(isBinarySearchTree(createBinaryTree({"a", "c", "b"})));
  EXPECT_FALSE(
      isBinarySearchTree(createBinaryTree({"a", "a", "a", "b", "b", "a"})));
}

}  // namespace tree::binary
