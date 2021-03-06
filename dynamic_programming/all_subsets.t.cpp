
#include <gtest/gtest.h>

#include "all_subsets.h"

namespace dp {
namespace {

using NumItems = std::size_t;
using NumExpectedSubsets = std::size_t;
using ExpectedOutcome = std::set<std::set<int>>;
using TestName = std::string;

struct TestCase {
  NumItems numItems{};

  NumExpectedSubsets numExpectedSubsets{};
  ExpectedOutcome expectedOutcome{};
};

}  // namespace

class TestAllSubsets : public ::testing::TestWithParam<TestCase> {
 public:
  static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
      -> std::string;
};

TEST_P(TestAllSubsets, testExtractAllSubSets) {
  const auto &param = TestAllSubsets::GetParam();

  auto source = std::set<int>();
  for (auto i = NumItems(0); i < param.numItems; i++) {
    source.insert(int(i));
  }
  ASSERT_EQ(param.numItems, source.size());

  auto actualOutcome = extractAllSubSets(source);
  EXPECT_EQ(param.numExpectedSubsets, actualOutcome.size());
  if (!param.expectedOutcome.empty()) {
    EXPECT_EQ(param.expectedOutcome, actualOutcome);
  }
}

INSTANTIATE_TEST_SUITE_P(
    TestAllSubsets, TestAllSubsets,
    testing::Values(

        TestCase{NumItems(0),            //
                 NumExpectedSubsets(1),  //
                 ExpectedOutcome{{}}},
        TestCase{NumItems(1),            //
                 NumExpectedSubsets(2),  //
                 ExpectedOutcome{{}, {0}}},
        TestCase{NumItems(2),            //
                 NumExpectedSubsets(4),  //
                 ExpectedOutcome{{}, {0}, {0, 1}, {1}}},
        TestCase{NumItems(3),  //
                 NumExpectedSubsets(8),
                 ExpectedOutcome{
                     {}, {0}, {0, 1}, {0, 1, 2}, {0, 2}, {1}, {1, 2}, {2}}},
        TestCase{NumItems(4),  //
                 NumExpectedSubsets(16),
                 ExpectedOutcome{{},
                                 {0},
                                 {0, 1},
                                 {0, 1, 2},
                                 {0, 1, 2, 3},
                                 {0, 1, 3},
                                 {0, 2},
                                 {0, 2, 3},
                                 {0, 3},
                                 {1},
                                 {1, 2},
                                 {1, 2, 3},
                                 {1, 3},
                                 {2},
                                 {2, 3},
                                 {3}}},
        TestCase{NumItems(10), NumExpectedSubsets(1UL << 10)},
        TestCase{NumItems(15), NumExpectedSubsets(1UL << 15)}

        ),
    &TestAllSubsets::getTestName);

auto TestAllSubsets::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
  return "n_" + std::to_string(testInfo.param.numItems);
}

}  // namespace dp
