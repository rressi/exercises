
#include "all_subsets.h"

#include <gtest/gtest.h>

namespace dynamic_programming {

using TestName = std::string;

struct UnitAllSubsets_TestCase {
    std::size_t numItems{};
    std::size_t numExpectedSubsets{};
    std::set<std::set<int>> expectedOutcome{};
};

class UnitAllSubsets : public ::testing::TestWithParam<UnitAllSubsets_TestCase> {

public:
    using TestCase = UnitAllSubsets_TestCase;

    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string;
};

TEST_P(UnitAllSubsets, test) {
    const auto &param = UnitAllSubsets::GetParam();

    auto source = std::set<int>();
    for (auto i = 0; i < int(param.numItems); i++) {
        source.insert(i);
    }
    ASSERT_EQ(param.numItems, source.size());

    auto actualOutcome = extractAllSubSets(source);
    EXPECT_EQ(param.numExpectedSubsets, actualOutcome.size());

    if (!param.expectedOutcome.empty()) {
        EXPECT_EQ(param.expectedOutcome, actualOutcome);
    }
}

INSTANTIATE_TEST_SUITE_P(UnitAllSubsets,
                         UnitAllSubsets,
                         testing::Values(

                                 UnitAllSubsets::TestCase{0, 1, {{}}},
                                 UnitAllSubsets::TestCase{1, 2, {{}, {0}}},
                                 UnitAllSubsets::TestCase{2, 4, {{}, {0}, {0, 1}, {1}}},
                                 UnitAllSubsets::TestCase{3, 8, {{}, {0}, {0, 1}, {0, 1, 2}, {0, 2}, {1}, {1, 2}, {2}}},
                                 UnitAllSubsets::TestCase{4, 16,
                                                          {{}, {0}, {0, 1}, {0, 1, 2}, {0, 1, 2, 3}, {0, 1, 3}, {0, 2},
                                                           {0, 2, 3}, {0, 3}, {1}, {1, 2}, {1, 2, 3}, {1, 3}, {2},
                                                           {2, 3}, {3}}},

                                 UnitAllSubsets::TestCase{10, 1UL << 10},
                                 UnitAllSubsets::TestCase{15, 1UL << 15}

                         ),
                         &UnitAllSubsets::getTestName);

auto UnitAllSubsets::getTestName(const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    return "n_" + std::to_string(testInfo.param.numItems);
}

} // namespace dynamic_programming
