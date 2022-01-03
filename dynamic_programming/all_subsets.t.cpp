
#include <gtest/gtest.h>

#include "all_subsets.h"


namespace dp {

using NumItems = std::size_t;
using NumExpectedSubsets = std::size_t;
using ExpectedOutcome = std::set<std::set<int>>;
using TestName = std::string;

struct TestAllSubsets_TestCase {
    NumItems numItems{};

    NumExpectedSubsets numExpectedSubsets{};
    ExpectedOutcome expectedOutcome{};
};

class TestAllSubsets
    : public ::testing::TestWithParam<TestAllSubsets_TestCase> {
   public:
    using TestCase = TestAllSubsets_TestCase;

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

        TestAllSubsets::TestCase{NumItems(0),  //
                                 NumExpectedSubsets(1), ExpectedOutcome{{}}},
        TestAllSubsets::TestCase{NumItems(1),  //
                                 NumExpectedSubsets(2),
                                 ExpectedOutcome{{}, {0}}},
        TestAllSubsets::TestCase{NumItems(2),  //
                                 NumExpectedSubsets(4),
                                 ExpectedOutcome{{}, {0}, {0, 1}, {1}}},
        TestAllSubsets::TestCase{
            NumItems(3),  //
            NumExpectedSubsets(8),
            ExpectedOutcome{
                {}, {0}, {0, 1}, {0, 1, 2}, {0, 2}, {1}, {1, 2}, {2}}},
        TestAllSubsets::TestCase{NumItems(4),  //
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
        TestAllSubsets::TestCase{NumItems(10), NumExpectedSubsets(1UL << 10)},
        TestAllSubsets::TestCase{NumItems(15), NumExpectedSubsets(1UL << 15)}

        ),
    &TestAllSubsets::getTestName);

auto TestAllSubsets::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    return "n_" + std::to_string(testInfo.param.numItems);
}

}  // namespace dp
