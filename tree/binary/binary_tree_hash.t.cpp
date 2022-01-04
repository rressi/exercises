
#include <gtest/gtest.h>
#include <zlib/zlib.h>

#include <ostream>
#include <string>
#include <tuple>

#include "binary_tree_hash.h"


namespace tree::binary {
namespace {

using NodeValue = std::string;
using InputValues = const std::vector<NodeValue>;

}  // namespace

class TestBinaryTreeHash : public ::testing::Test {
 public:
  void runTest(const InputValues& inputValues, HashCode expectedHahs) const;

 protected:
  auto generateExpectedHash(const InputValues& InputValues, std ::size_t first,
                            std ::size_t last) const -> HashCode;
};

TEST_F(TestBinaryTreeHash, testVisit_depth1) { runTest(InputValues{"0"}, 0); }

TEST_F(TestBinaryTreeHash, testVisit_depth2) {
  runTest(InputValues{"0", "1", "2"}, 0);
}

TEST_F(TestBinaryTreeHash, testVisit_depth3) {
  runTest(InputValues{"0", "1", "2", "3", "4", "5", "6"}, 0);
}

void TestBinaryTreeHash::runTest(const InputValues& inputValues,
                                 HashCode expectedHahs) const {
  auto tree = createBinaryTree(inputValues);

  auto actualHashCode = hashTree(*tree);
  auto expectedHashCode =
      generateExpectedHash(inputValues, 0, inputValues.size());

  EXPECT_EQ(expectedHashCode, actualHashCode);
}

auto TestBinaryTreeHash::generateExpectedHash(const InputValues& inputValues,
                                              std ::size_t first,
                                              std ::size_t last) const
    -> HashCode {
  auto pivot = first + ((last - first) / 2);
  const auto& value = inputValues[pivot];

  auto treeHash =
      ::crc32(HASH_NODE_SEED, reinterpret_cast<const Bytef*>(value.data()),
              value.size());

  if (pivot > first) {
    auto leftHash = generateExpectedHash(inputValues, first, pivot);
    treeHash ^= leftHash * HASH_NODE_COMBINE_FACTOR_LEFT;
  }
  if (pivot + 1 < last) {
    auto rightHash = generateExpectedHash(inputValues, pivot + 1, last);
    treeHash ^= rightHash * HASH_NODE_COMBINE_FACTOR_RIGHT;
  }

  return treeHash;
}

}  // namespace tree::binary
