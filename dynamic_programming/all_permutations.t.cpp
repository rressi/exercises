
#include <gtest/gtest.h>

#include "all_permutations.h"


namespace dp {
namespace {

using NumItems = std::size_t;
using NumExpectedPermutations = std::size_t;
using ExpectedOutcome = std::unordered_set<std::string>;

struct TestCase {
    NumItems numItems{};
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
    input.reserve(param.numItems);
    for (auto i = NumItems(0); i < param.numItems; i++) {
        input.push_back('a' + i);
    }
    ASSERT_EQ(param.numItems, input.size());

    auto actualOutcome = extractAllPermutations(input);
    EXPECT_EQ(param.numExpectedPermuations, actualOutcome.size());
    if (!param.expectedOutcome.empty()) {
        EXPECT_EQ(param.expectedOutcome, actualOutcome);
    }
}

INSTANTIATE_TEST_SUITE_P(ZeroToThree, TestAllPermutations,
                         testing::Values(

                             TestCase{NumItems(0),                 //
                                      NumExpectedPermutations(0),  //
                                      ExpectedOutcome{}},
                             TestCase{NumItems(1),                 //
                                      NumExpectedPermutations(1),  //
                                      ExpectedOutcome{"a"}},
                             TestCase{NumItems(2),                 //
                                      NumExpectedPermutations(2),  //
                                      ExpectedOutcome{"ab", "ba"}},
                             TestCase{NumItems(3),                 //
                                      NumExpectedPermutations(6),  //
                                      ExpectedOutcome{"abc", "acb", "bac",
                                                      "bca", "cab", "cba"}}

                             ),
                         &TestAllPermutations::getTestName);

INSTANTIATE_TEST_SUITE_P(
    FourToTen, TestAllPermutations,
    testing::Values(

        TestCase{NumItems(4), NumExpectedPermutations(24)},
        TestCase{NumItems(5), NumExpectedPermutations(120)},
        TestCase{NumItems(6), NumExpectedPermutations(720)},
        TestCase{NumItems(7), NumExpectedPermutations(5'040)},
        TestCase{NumItems(8), NumExpectedPermutations(40'320)}

        ),
    &TestAllPermutations::getTestName);

auto TestAllPermutations::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    return "n_" + std::to_string(testInfo.param.numItems);
}

}  // namespace dp
