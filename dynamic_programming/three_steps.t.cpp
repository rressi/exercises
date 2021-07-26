
#include "three_steps.h"

#include <gtest/gtest.h>

namespace dynamic_programming {

struct TestCase {
    int input{};
    int expectedOutcome{};
};


class UnitThreeSteps : public ::testing::TestWithParam<TestCase> {

public:
    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string;

};

TEST_P(UnitThreeSteps, test) {
    const auto &param = UnitThreeSteps::GetParam();
    EXPECT_EQ(param.expectedOutcome, count_combinations_in_climbing_stairs(param.input));
}

INSTANTIATE_TEST_SUITE_P(UnitThreeSteps,
                         UnitThreeSteps,
                         testing::Values(

                                 TestCase{},
                                 TestCase{1, 1},
                                 TestCase{2, 2},
                                 TestCase{3, 3},
                                 TestCase{4, 6},
                                 TestCase{5, 11},
                                 TestCase{6, 20},
                                 TestCase{7, 37}

                         ),
                         &UnitThreeSteps::getTestName);

auto UnitThreeSteps::getTestName(const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    const auto &param = testInfo.param;
    return "n_" + std::to_string(param.input);
}

} // namespace edit_distance
