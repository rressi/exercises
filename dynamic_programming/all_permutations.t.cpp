
#include <gtest/gtest.h>

#include "all_permutations.h"

namespace dp {
namespace {

using NumItems = std::size_t;
using NumExpectedPermutations = std::size_t;
using ExpectedOutcome = AllPermutations<std::string>;
using DinstinctChars = bool;

struct TestCase {
  NumItems numItems{};
  DinstinctChars distrinctChars{};

  NumExpectedPermutations numExpectedPermuations{};
  ExpectedOutcome expectedOutcome{};
};

}  // namespace

class TestAllPermutations : public ::testing::TestWithParam<TestCase> {
 public:
  static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
      -> std::string;
};

TEST_P(TestAllPermutations, testExtractAllPermutations) {
  const auto &param = TestAllPermutations::GetParam();

  auto input = std::string();
  if (param.distrinctChars) {
    input.reserve(param.numItems);
    for (auto i = NumItems(0); i < param.numItems; i++) {
      input.push_back('a' + i);
    }
  } else {
    auto moduloFactor =
        std::max<NumItems>(1, (param.numItems / 2) + (param.numItems & 1));
    for (auto i = NumItems(0); i < param.numItems; i++) {
      input.push_back('a' + (i % moduloFactor));
    }
  }
  ASSERT_EQ(param.numItems, input.size());

  auto actualOutcome = extractAllPermutations(input);
  EXPECT_EQ(param.numExpectedPermuations, actualOutcome.size());
  if (!param.expectedOutcome.empty()) {
    EXPECT_EQ(param.expectedOutcome, actualOutcome);
  }
}

INSTANTIATE_TEST_SUITE_P(
    ZeroToThree, TestAllPermutations,
    testing::Values(

        TestCase{NumItems(0), DinstinctChars{true},

                 NumExpectedPermutations(0), ExpectedOutcome{}},

        TestCase{NumItems(1), DinstinctChars{true},

                 NumExpectedPermutations(1), ExpectedOutcome{"a"}},

        TestCase{NumItems(2), DinstinctChars{true},

                 NumExpectedPermutations(2), ExpectedOutcome{"ab", "ba"}},

        TestCase{NumItems(3), DinstinctChars{true},

                 NumExpectedPermutations(6),
                 ExpectedOutcome{"abc", "acb", "bac", "bca", "cab", "cba"}},

        TestCase{NumItems(0), DinstinctChars{false},

                 NumExpectedPermutations(0), ExpectedOutcome{}},

        TestCase{NumItems(1), DinstinctChars{false},

                 NumExpectedPermutations(1), ExpectedOutcome{"a"}},

        TestCase{NumItems(2), DinstinctChars{false},

                 NumExpectedPermutations(1), ExpectedOutcome{"aa"}},

        TestCase{NumItems(3), DinstinctChars{false},

                 NumExpectedPermutations(3),
                 ExpectedOutcome{"aab", "aba", "baa"}}

        ),
    &TestAllPermutations::getTestName);

INSTANTIATE_TEST_SUITE_P(FourToTen, TestAllPermutations,
                         testing::Values(

                             TestCase{NumItems(4), DinstinctChars{true},

                                      NumExpectedPermutations(24)},

                             TestCase{NumItems(5), DinstinctChars{true},

                                      NumExpectedPermutations(120)},

                             TestCase{NumItems(6), DinstinctChars{true},

                                      NumExpectedPermutations(720)},

                             TestCase{NumItems(7), DinstinctChars{true},

                                      NumExpectedPermutations(5'040)},

                             TestCase{NumItems(8), DinstinctChars{true},

                                      NumExpectedPermutations(40'320)},

                             TestCase{NumItems(4), DinstinctChars{false},

                                      NumExpectedPermutations(6)},

                             TestCase{NumItems(5), DinstinctChars{false},

                                      NumExpectedPermutations(30)},

                             TestCase{NumItems(6), DinstinctChars{false},

                                      NumExpectedPermutations(90)},

                             TestCase{NumItems(7), DinstinctChars{false},

                                      NumExpectedPermutations(630)},

                             TestCase{NumItems(8), DinstinctChars{false},

                                      NumExpectedPermutations(2'520)}

                             ),
                         &TestAllPermutations::getTestName);

auto TestAllPermutations::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
  auto testName = "n_" + std::to_string(testInfo.param.numItems);
  if (testInfo.param.distrinctChars) {
    testName.append("_distrinctChars");
  }
  return testName;
}

}  // namespace dp
