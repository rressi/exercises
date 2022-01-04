
#include <gtest/gtest.h>

#include "robot_navigator.h"

namespace dp::robot_navigator {
namespace {

using TestName = std::string;

struct TestCase {
  TestName testName{};
  Blockers inputGrid{};
  Opt<Path> expectedOutcome{};
};

}  // namespace

class TestRobotNavigator : public ::testing::TestWithParam<TestCase> {
 public:
  static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
      -> std::string;
};

TEST_P(TestRobotNavigator, test) {
  const auto &param = TestRobotNavigator::GetParam();

  auto actualOucome = findPath(param.inputGrid);
  EXPECT_EQ(param.expectedOutcome, actualOucome);
}

INSTANTIATE_TEST_SUITE_P(
    TestRobotNavigator, TestRobotNavigator,
    testing::Values(

        TestCase{TestName{"grid_1x1"}, Blockers{{false}}, Path{Pos{0, 0}}},
        TestCase{TestName{"grid_2x2"}, Blockers{{false, false}, {false, false}},
                 Path{Pos{0, 0}, Pos{0, 1}, Pos{1, 1}}},
        TestCase{TestName{"grid_3x3"},
                 Blockers{{false, false, false},
                          {false, false, false},
                          {false, false, false}},
                 Path{Pos{0, 0}, Pos{0, 1}, Pos{0, 2}, Pos{1, 2}, Pos{2, 2}}},

        TestCase{TestName{"grid_1x1_obstruction"}, Blockers{{true}}, {}},

        TestCase{TestName{"grid_2x2_obstruction_1"},
                 Blockers{{false, true}, {true, false}},
                 {}},
        TestCase{TestName{"grid_2x2_obstruction_2"},
                 Blockers{{true, false}, {true, false}},
                 {}},
        TestCase{TestName{"grid_2x2_obstruction_3"},
                 Blockers{{false, true}, {false, true}},
                 {}},

        TestCase{TestName{"grid_3x3_obstruction_1"},
                 Blockers{{false, true, false},
                          {false, true, false},
                          {false, true, false}},
                 {}},
        TestCase{TestName{"grid_3x3_obstruction_2"},
                 Blockers{{false, false, true},
                          {false, true, false},
                          {true, false, false}},
                 {}},
        TestCase{TestName{"grid_3x3_obstruction_3"},
                 Blockers{{false, false, false},
                          {true, true, true},
                          {false, false, false}},
                 {}},
        TestCase{
            TestName{"grid_3x3_obstruction_4"},
            Blockers{{false, true, false},
                     {true, false, false},
                     {false, false, false}},
            {},
        },
        TestCase{
            TestName{"grid_3x3_obstruction_5"},
            Blockers{{false, false, false},
                     {false, false, true},
                     {false, true, false}},
            {},
        },

        TestCase{TestName{"grid_3x3_labyrinth_1"},
                 Blockers{{false, true, true},
                          {false, false, false},
                          {true, true, false}},
                 Path{Pos{0, 0}, Pos{0, 1}, Pos{1, 1}, Pos{2, 1}, Pos{2, 2}}}

        ),
    &TestRobotNavigator::getTestName);

auto TestRobotNavigator::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
  return testInfo.param.testName;
}

}  // namespace dp::robot_navigator
