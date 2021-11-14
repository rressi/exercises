
#include "robot_navigator.h"

#include <gtest/gtest.h>

namespace dynamic_programming::robot_navigator {

using TestName = std::string;

struct UnitRobotNavigator_TestCase {
    TestName testName{};
    Blockers inputGrid{};
    Opt<Path> expectedOutcome{};
};

class UnitRobotNavigator : public ::testing::TestWithParam<UnitRobotNavigator_TestCase> {

public:
    using TestCase = UnitRobotNavigator_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string;
};

TEST_P(UnitRobotNavigator, test) {
    const auto &param = UnitRobotNavigator::GetParam();

    EXPECT_EQ(param.expectedOutcome, findPath(param.inputGrid));
}

INSTANTIATE_TEST_SUITE_P(UnitRobotNavigator,
                         UnitRobotNavigator,
                         testing::Values(

                                 UnitRobotNavigator::TestCase{TestName{"grid_1x1"},
                                                              Blockers{{false}},
                                                              Path{Pos{0, 0}}
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_2x2"},
                                                              Blockers{{false, false},
                                                                       {false, false}},
                                                              Path{Pos{0, 0}, Pos{0, 1}, Pos{1, 1}}
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_3x3"},
                                                              Blockers{{false, false, false},
                                                                       {false, false, false},
                                                                       {false, false, false}},
                                                              Path{Pos{0, 0}, Pos{0, 1}, Pos{0, 2}, Pos{1, 2},
                                                                   Pos{2, 2}}
                                 },

                                 UnitRobotNavigator::TestCase{TestName{"grid_1x1_obstruction"},
                                                              Blockers{{true}},
                                                              {}
                                 },

                                 UnitRobotNavigator::TestCase{TestName{"grid_2x2_obstruction_1"},
                                                              Blockers{{false, true},
                                                                       {true,  false}},
                                                              {}
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_2x2_obstruction_2"},
                                                              Blockers{{true, false},
                                                                       {true, false}},
                                                              {}
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_2x2_obstruction_3"},
                                                              Blockers{{false, true},
                                                                       {false, true}},
                                                              {}
                                 },

                                 UnitRobotNavigator::TestCase{TestName{"grid_3x3_obstruction_1"},
                                                              Blockers{{false, true, false},
                                                                       {false, true, false},
                                                                       {false, true, false}},
                                                              {}
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_3x3_obstruction_2"},
                                                              Blockers{{false, false, true},
                                                                       {false, true,  false},
                                                                       {true,  false, false}},
                                                              {}
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_3x3_obstruction_3"},
                                                              Blockers{{false, false, false},
                                                                       {true,  true,  true},
                                                                       {false, false, false}},
                                                              {}
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_3x3_obstruction_4"},
                                                              Blockers{{false, true,  false},
                                                                       {true,  false, false},
                                                                       {false, false, false}},
                                                              {},
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_3x3_obstruction_5"},
                                                              Blockers{{false, false, false},
                                                                       {false, false, true},
                                                                       {false, true,  false}},
                                                              {},
                                 },

                                 UnitRobotNavigator::TestCase{TestName{"grid_3x3_labyrinth_1"},
                                                              Blockers{{false, true,  true},
                                                                       {false, false, false},
                                                                       {true,  true,  false}},
                                                              Path{Pos{0, 0}, Pos{0, 1}, Pos{1, 1}, Pos{2, 1},
                                                                   Pos{2, 2}}
                                 }

                         ),
                         &UnitRobotNavigator::getTestName);

auto UnitRobotNavigator::getTestName(const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    return testInfo.param.testName;
}

} // namespace edit_distance
