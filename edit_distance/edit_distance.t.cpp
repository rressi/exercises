
#include "edit_distance.h"

#include <gtest/gtest.h>

namespace edit_distance {

struct TestCase {
    std::string a{};
    std::string b{};
    std::size_t maxDistance{0};
    bool expectedOutcome{true};
};


class UnitEditDistance : public ::testing::TestWithParam<TestCase> {

public:
    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string;

};

TEST_P(UnitEditDistance, testMatchStrings) {
    const auto &param = UnitEditDistance::GetParam();
    EXPECT_EQ(param.expectedOutcome, matchStrings(param.a, param.b, param.maxDistance));
}

INSTANTIATE_TEST_SUITE_P(UnitEditDistance,
                         UnitEditDistance,
                         testing::Values(

                                 TestCase{"foo", "foo", 0, true},
                                 TestCase{"foo", "fo1", 0, false},
                                 TestCase{"a", "", 0, false},
                                 TestCase{"", "b", 0, false},

                                 TestCase{"fo1", "fo2", 1, true},
                                 TestCase{"fo", "fo2", 1, true},
                                 TestCase{"fo1", "fo", 1, true},
                                 TestCase{"a", "", 1, true},
                                 TestCase{"", "b", 1, true},

                                 TestCase{"fo12", "fo34", 1, false},
                                 TestCase{"fo", "fo34", 1, false},
                                 TestCase{"fo12", "fo", 1, false},

                                 TestCase{"abc", "ac", 0, false},
                                 TestCase{"abc", "bc", 0, false},
                                 TestCase{"abc", "ac", 1, true},
                                 TestCase{"abc", "bc", 1, true},

                                 TestCase{"underground", "undrground", 1, true},
                                 TestCase{"underground", "undrgrund", 1, false},
                                 TestCase{"underground", "undrgrund", 2, true},
                                 TestCase{"underground", "undrgrunz", 2, false},

                                 TestCase{}
                         ),
                         &UnitEditDistance::getTestName);

auto UnitEditDistance::getTestName(const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {

    const auto &param = testInfo.param;
    return std::string(param.a) + "_" + std::string(param.b) + "_" + std::to_string(param.maxDistance) + "_" +
           std::to_string(param.expectedOutcome);
}

} // namespace edit_distance
