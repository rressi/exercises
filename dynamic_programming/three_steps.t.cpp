
#include "three_steps.h"

#include <gtest/gtest.h>

namespace dynamic_programming {

struct UnitThreeSteps_TestCase {
    std::int64_t input{};
    std::int64_t expectedOutcome{};
};


class UnitThreeSteps : public ::testing::TestWithParam<UnitThreeSteps_TestCase> {

public:
    using TestCase = UnitThreeSteps_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string;

};

TEST_P(UnitThreeSteps, test_count_combinations_in_climbing_stairs) {
    const auto &param = UnitThreeSteps::GetParam();
    EXPECT_EQ(param.expectedOutcome, count_combinations_in_climbing_stairs(param.input));
}

TEST_P(UnitThreeSteps, test_count_combinations_in_climbing_stairs_recursive) {
    const auto &param = UnitThreeSteps::GetParam();
    EXPECT_EQ(param.expectedOutcome, count_combinations_in_climbing_stairs_recursive(param.input));
}

INSTANTIATE_TEST_SUITE_P(UnitThreeSteps,
                         UnitThreeSteps,
                         testing::Values(

                                 UnitThreeSteps_TestCase{-1, 0},
                                 UnitThreeSteps_TestCase{0, 1},
                                 UnitThreeSteps_TestCase{1, 1},
                                 UnitThreeSteps_TestCase{2, 2},
                                 UnitThreeSteps_TestCase{3, 4},
                                 UnitThreeSteps_TestCase{4, 7},
                                 UnitThreeSteps_TestCase{5, 13},
                                 UnitThreeSteps_TestCase{6, 24},
                                 UnitThreeSteps_TestCase{7, 44},

                                 UnitThreeSteps_TestCase{40, 23'837'527'729}

                         ),
                         &UnitThreeSteps::getTestName);

auto UnitThreeSteps::getTestName(const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    const auto &param = testInfo.param;
    if (param.input < 0) {
        return "n_minus_" + std::to_string(-param.input);
    } else {
        return "n_" + std::to_string(param.input);
    }
}

} // namespace edit_distance
