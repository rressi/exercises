
#include <gtest/gtest.h>

#include <map>
#include <sstream>

#include "tree.h"

namespace tree {

using NumNodes = std::size_t;
using VisitOrder = Tree::VisitOrder;
using TestVisitTree_TestCase = std::tuple<NumNodes, VisitOrder>;

class TestVisitTree : public ::testing::TestWithParam<TestVisitTree_TestCase> {
 public:
  using TestCase = TestVisitTree_TestCase;

  static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
      -> std::string;

 protected:
  auto getNumNodes() const -> NumNodes;
  auto getVisitOrder() const -> VisitOrder;

  using Depth = Tree::Depth;
  using NumericValue = std::uint32_t;
  using GraphDump = std::map<Depth, std::vector<NumericValue>>;

  auto createInputValues() -> std::vector<pb::Value>;
  auto createActualDump(const Opt<Tree> &tree) const -> GraphDump;
  auto createExpectedDump() const -> Opt<GraphDump>;
};

INSTANTIATE_TEST_SUITE_P(
    TestVisitTree, TestVisitTree,
    testing::Combine(testing::Values(0, 1, 3, 7),
                     testing::Values(

                         VisitOrder::BREATH_FIRST, VisitOrder::DEPTH_FIRST,
                         VisitOrder::PRE_ORDER, VisitOrder::IN_ORDER,
                         VisitOrder::POST_ORDER

                         )),
    &TestVisitTree::getTestName);

TEST_P(TestVisitTree, testCreateBinaryTree) {
  auto inputValues = createInputValues();

  auto tree = createBinaryTree(inputValues, getVisitOrder());

  auto actualDump = createActualDump(tree);
  auto expectedDump = createExpectedDump();
  ASSERT_TRUE(expectedDump);
  ASSERT_EQ(expectedDump.value(), actualDump);
}

namespace {

auto toString(VisitOrder visitOrder) -> const char * {
  switch (visitOrder) {
    case VisitOrder::DEPTH_FIRST:
      return "DEPTH_FIRST";
    case VisitOrder::BREATH_FIRST:
      return "BREATH_FIRST";
    case VisitOrder::PRE_ORDER:
      return "PRE_ORDER";
    case VisitOrder::IN_ORDER:
      return "IN_ORDER";
    case VisitOrder::POST_ORDER:
      return "POST_ORDER";
    default:
      throw std::runtime_error("Invalid visit order:" +
                               std::to_string(int(visitOrder)));
  }
}

}  // namespace

auto operator<<(std::ostream &out, const TestVisitTree::TestCase &testCase)
    -> std::ostream & {
  out << "numNodes_" << std::get<0>(testCase);
  out << "__visitOrder_" << toString(std::get<1>(testCase));
  return out;
}

auto TestVisitTree::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
  std::stringstream buf;
  buf << testInfo.param;
  return buf.str();
}

auto TestVisitTree::getNumNodes() const -> NumNodes {
  return std::get<0>(TestVisitTree::GetParam());
}

auto TestVisitTree::getVisitOrder() const -> VisitOrder {
  return std::get<1>(TestVisitTree::GetParam());
}

auto TestVisitTree::createInputValues() -> std::vector<pb::Value> {
  auto inputValues = std::vector<pb::Value>();

  auto numNodes = getNumNodes();
  inputValues.reserve(numNodes);

  for (auto numericValue = NumNodes(); numericValue < numNodes;
       numericValue++) {
    inputValues.emplace_back();
    inputValues.back().set_numeric(numericValue);
  }

  return inputValues;
}

auto TestVisitTree::createActualDump(const Opt<Tree> &tree) const -> GraphDump {
  if (!tree) return {};

  auto graphDump = GraphDump();
  auto dumpNode = [&](const pb::Node &node, Depth depth) {
    auto numericValue = node.has_value() ? node.value().numeric() : -1;
    graphDump[depth].push_back(numericValue);
    return Tree::VisitStatus::CONTINUE;
  };
  tree->visit(dumpNode, VisitOrder::BREATH_FIRST);

  return graphDump;
}

auto TestVisitTree::createExpectedDump() const -> Opt<GraphDump> {
  switch (getNumNodes()) {
    case 0:
      return GraphDump{};
    case 1:
      return GraphDump{{0, {0}}};
    default:
      break;
  }

  switch (getVisitOrder()) {
    case VisitOrder::DEPTH_FIRST:
    case VisitOrder::PRE_ORDER:
      switch (getNumNodes()) {
        case 3:
          return GraphDump{{0, {0}}, {1, {1, 2}}};
        case 7:
          return GraphDump{{0, {0}}, {1, {1, 4}}, {2, {2, 3, 5, 6}}};
      }
      break;

    case VisitOrder::BREATH_FIRST:
      switch (getNumNodes()) {
        case 3:
          return GraphDump{{0, {0}}, {1, {1, 2}}};
        case 7:
          return GraphDump{{0, {0}}, {1, {1, 2}}, {2, {3, 4, 5, 6}}};
      }
      break;

    case VisitOrder::IN_ORDER:
      switch (getNumNodes()) {
        case 3:
          return GraphDump{{0, {1}}, {1, {0, 2}}};
        case 7:
          return GraphDump{{0, {3}}, {1, {1, 5}}, {2, {0, 2, 4, 6}}};
      }
      break;

    case VisitOrder::POST_ORDER:
      switch (getNumNodes()) {
        case 3:
          return GraphDump{{0, {2}}, {1, {0, 1}}};
        case 7:
          return GraphDump{{0, {6}}, {1, {2, 5}}, {2, {0, 1, 3, 4}}};
      }
      break;
  }

  return {};
}

}  // namespace tree
