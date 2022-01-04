#include <gtest/gtest.h>

#include <iostream>

#include "three_steps.h"

namespace dp {
namespace {

struct TestCase {
  std::int64_t input{};
  std::int64_t expectedOutcome{};
};

}  // namespace

class TestThreeSteps : public ::testing::TestWithParam<TestCase> {
 public:
  static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
      -> std::string;
};

TEST_P(TestThreeSteps, testCountCombinationsInClimbingStairs) {
  const auto &param = TestThreeSteps::GetParam();
  EXPECT_EQ(param.expectedOutcome,
            countCombinationsInClimbingStairs(param.input));
}

TEST_P(TestThreeSteps, testCountCombinationsInClimbingStairsRecursive) {
  const auto &param = TestThreeSteps::GetParam();
  EXPECT_EQ(param.expectedOutcome,
            countCombinationsInClimbingStairsRecursive(param.input));
}

INSTANTIATE_TEST_SUITE_P(TestThreeSteps, TestThreeSteps,
                         testing::Values(

                             TestCase{-1, 0}, TestCase{0, 1}, TestCase{1, 1},
                             TestCase{2, 2}, TestCase{3, 4}, TestCase{4, 7},
                             TestCase{5, 13}, TestCase{6, 24}, TestCase{7, 44},

                             TestCase{40, 23'837'527'729}

                             ),
                         &TestThreeSteps::getTestName);

auto TestThreeSteps::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
  const auto &param = testInfo.param;
  if (param.input < 0) {
    return "n_minus_" + std::to_string(-param.input);
  } else {
    return "n_" + std::to_string(param.input);
  }
}

auto operator<<(std::ostream &out, const TestCase &testCase) -> std::ostream & {
  out << "{\"input\": \"" << testCase.input << "\", \"expectedOutcome\": \""
      << testCase.expectedOutcome << "\"}";
  return out;
}

}  // namespace dp
