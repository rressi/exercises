
#include "robot_navigator.h"

#include <gtest/gtest.h>

namespace dynamic_programming {

using TestName = std::string;

using Cell = RobotNavigator::Cell;
using Grid = RobotNavigator::Grid;
using Path = RobotNavigator::Path;
using Pos = RobotNavigator::Pos;

struct UnitRobotNavigator_TestCase {
    TestName testName{};
    Grid inputGrid{};
    Opt<Path> expectedOutcome{};
};

class UnitRobotNavigator : public ::testing::TestWithParam<UnitRobotNavigator_TestCase> {

public:
    using TestCase = UnitRobotNavigator_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string;
};

TEST_P(UnitRobotNavigator, test) {
    const auto &param = UnitRobotNavigator::GetParam();

    auto width = std::max(0, int(param.inputGrid.size()));
    ASSERT_LT(0, width);

    auto height = std::max(0, int(param.inputGrid.front().size()));
    ASSERT_LT(0, height);

    auto from = Pos{0, 0};
    auto to = Pos{width - 1, height - 1};

    EXPECT_EQ(param.expectedOutcome, RobotNavigator(param.inputGrid).findRoute(from, to));
}

INSTANTIATE_TEST_SUITE_P(UnitRobotNavigator,
                         UnitRobotNavigator,
                         testing::Values(

                                 UnitRobotNavigator::TestCase{TestName{"grid_1x1"},
                                                              Grid{{Cell::Valid}},
                                                              Path{Pos{0, 0}}
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_2x2"},
                                                              Grid{{Cell::Valid, Cell::Valid},
                                                                   {Cell::Valid, Cell::Valid}},
                                                              Path{Pos{0, 0}, Pos{0, 1}, Pos{1, 1}}
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_3x3"},
                                                              Grid{{Cell::Valid, Cell::Valid, Cell::Valid},
                                                                   {Cell::Valid, Cell::Valid, Cell::Valid},
                                                                   {Cell::Valid, Cell::Valid, Cell::Valid}},
                                                              Path{Pos{0, 0}, Pos{0, 1}, Pos{0, 2}, Pos{1, 2},
                                                                   Pos{2, 2}}
                                 },

                                 UnitRobotNavigator::TestCase{TestName{"grid_1x1_obstruction"},
                                                              Grid{{Cell::Invalid}},
                                                              {}
                                 },

                                 UnitRobotNavigator::TestCase{TestName{"grid_2x2_obstruction_1"},
                                                              Grid{{Cell::Valid,   Cell::Invalid},
                                                                   {Cell::Invalid, Cell::Valid}},
                                                              {}
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_2x2_obstruction_2"},
                                                              Grid{{Cell::Invalid, Cell::Valid},
                                                                   {Cell::Invalid, Cell::Valid}},
                                                              {}
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_2x2_obstruction_3"},
                                                              Grid{{Cell::Valid, Cell::Invalid},
                                                                   {Cell::Valid, Cell::Invalid}},
                                                              {}
                                 },

                                 UnitRobotNavigator::TestCase{TestName{"grid_3x3_obstruction_1"},
                                                              Grid{{Cell::Valid, Cell::Invalid, Cell::Valid},
                                                                   {Cell::Valid, Cell::Invalid, Cell::Valid},
                                                                   {Cell::Valid, Cell::Invalid, Cell::Valid}},
                                                              {}
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_3x3_obstruction_2"},
                                                              Grid{{Cell::Valid,   Cell::Valid,   Cell::Invalid},
                                                                   {Cell::Valid,   Cell::Invalid, Cell::Valid},
                                                                   {Cell::Invalid, Cell::Valid,   Cell::Valid}},
                                                              {}
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_3x3_obstruction_3"},
                                                              Grid{{Cell::Valid,   Cell::Valid,   Cell::Valid},
                                                                   {Cell::Invalid, Cell::Invalid, Cell::Invalid},
                                                                   {Cell::Valid,   Cell::Valid,   Cell::Valid}},
                                                              {}
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_3x3_obstruction_4"},
                                                              Grid{{Cell::Valid,   Cell::Invalid, Cell::Valid},
                                                                   {Cell::Invalid, Cell::Valid,   Cell::Valid},
                                                                   {Cell::Valid,   Cell::Valid,   Cell::Valid}},
                                                              {},
                                 },
                                 UnitRobotNavigator::TestCase{TestName{"grid_3x3_obstruction_5"},
                                                              Grid{{Cell::Valid, Cell::Valid,   Cell::Valid},
                                                                   {Cell::Valid, Cell::Valid,   Cell::Invalid},
                                                                   {Cell::Valid, Cell::Invalid, Cell::Valid}},
                                                              {},
                                 },

                                 UnitRobotNavigator::TestCase{TestName{"grid_3x3_labyrinth_1"},
                                                              Grid{{Cell::Valid,   Cell::Invalid, Cell::Invalid},
                                                                   {Cell::Valid,   Cell::Valid,   Cell::Valid},
                                                                   {Cell::Invalid, Cell::Invalid, Cell::Valid}},
                                                              Path{Pos{0, 0}, Pos{0, 1}, Pos{1, 1}, Pos{2, 1},
                                                                   Pos{2, 2}}
                                 }

                         ),
                         &UnitRobotNavigator::getTestName);

auto UnitRobotNavigator::getTestName(const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    return testInfo.param.testName;
}

} // namespace edit_distance
