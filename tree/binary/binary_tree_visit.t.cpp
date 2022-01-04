
#include <gtest/gtest.h>

#include <ostream>
#include <string>
#include <tuple>

#include "binary_tree_visit.h"


namespace tree::binary {
namespace {

using NodeValue = std::string;
using InputValues = const std::vector<NodeValue>;
using VisitSequenceItem = std::tuple<VisitEvent, Depth, NodeValue>;
using VisitSequence = std::vector<VisitSequenceItem>;

auto operator<<(std::ostream& out, const VisitEvent& visitEvent)
    -> std::ostream& {
  out << toString(visitEvent);
  return out;
}

}  // namespace

class TestBinaryTreeVisit : public ::testing::Test {
 public:
  void runTest(const InputValues& inputValues,
               const VisitSequence& expectedVisitSequence) const;
};

TEST_F(TestBinaryTreeVisit, testVisit_depth1) {
  runTest(InputValues{"0"},  //
          VisitSequence{

              {VisitEvent::PRE_ORDER, 0, "0"},
              {VisitEvent::IN_ORDER, 0, "0"},
              {VisitEvent::POST_ORDER, 0, "0"},

          });
}

TEST_F(TestBinaryTreeVisit, testVisit_depth2) {
  runTest(InputValues{"0", "1", "2"},
          VisitSequence{

              {VisitEvent::PRE_ORDER, 0, "1"},
              /**/ {VisitEvent::PRE_ORDER, 1, "0"},
              /**/ {VisitEvent::IN_ORDER, 1, "0"},
              /**/ {VisitEvent::POST_ORDER, 1, "0"},
              {VisitEvent::IN_ORDER, 0, "1"},
              /**/ {VisitEvent::PRE_ORDER, 1, "2"},
              /**/ {VisitEvent::IN_ORDER, 1, "2"},
              /**/ {VisitEvent::POST_ORDER, 1, "2"},
              {VisitEvent::POST_ORDER, 0, "1"},

          }

  );
}

TEST_F(TestBinaryTreeVisit, testVisit_depth3) {
  runTest(InputValues{"0", "1", "2", "3", "4", "5", "6"},
          VisitSequence{

              {VisitEvent::PRE_ORDER, 0, "3"},
              /**/ {VisitEvent::PRE_ORDER, 1, "1"},
              /*  */ {VisitEvent::PRE_ORDER, 2, "0"},
              /*  */ {VisitEvent::IN_ORDER, 2, "0"},
              /*  */ {VisitEvent::POST_ORDER, 2, "0"},
              /**/ {VisitEvent::IN_ORDER, 1, "1"},
              /*  */ {VisitEvent::PRE_ORDER, 2, "2"},
              /*  */ {VisitEvent::IN_ORDER, 2, "2"},
              /*  */ {VisitEvent::POST_ORDER, 2, "2"},
              /**/ {VisitEvent::POST_ORDER, 1, "1"},
              {VisitEvent::IN_ORDER, 0, "3"},
              /**/ {VisitEvent::PRE_ORDER, 1, "5"},
              /*  */ {VisitEvent::PRE_ORDER, 2, "4"},
              /*  */ {VisitEvent::IN_ORDER, 2, "4"},
              /*  */ {VisitEvent::POST_ORDER, 2, "4"},
              /**/ {VisitEvent::IN_ORDER, 1, "5"},
              /*  */ {VisitEvent::PRE_ORDER, 2, "6"},
              /*  */ {VisitEvent::IN_ORDER, 2, "6"},
              /*  */ {VisitEvent::POST_ORDER, 2, "6"},
              /**/ {VisitEvent::POST_ORDER, 1, "5"},

              {VisitEvent::POST_ORDER, 0, "3"},

          });
}

void TestBinaryTreeVisit::runTest(
    const InputValues& inputValues,
    const VisitSequence& expectedVisitSequence) const {
  auto tree = createBinaryTree(inputValues);

  auto actualVisitSequence = VisitSequence();
  auto status = visit(*tree, [&](const VisitContext& visitContext) {
    actualVisitSequence.emplace_back(visitContext.event(), visitContext.depth(),
                                     visitContext.node().value);
    return VisitStatus::CONTINUE;
  });

  EXPECT_EQ(VisitStatus::CONTINUE, status);
  EXPECT_EQ(expectedVisitSequence.size(), actualVisitSequence.size());
  EXPECT_EQ(expectedVisitSequence, actualVisitSequence);
}

}  // namespace tree::binary
