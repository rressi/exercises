
#include <gtest/gtest.h>

#include "hex_bin_match.h"

namespace hex_bin_match {

struct TestCase {
    HexStringView hex{};
    BinStringView bin{};
    bool expectedOutcome{};
};

class UnitHexBinMatch : public ::testing::TestWithParam<TestCase> {
   public:
    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
        -> std::string;
};

TEST_P(UnitHexBinMatch, run) {
    const auto &param = UnitHexBinMatch::GetParam();
    EXPECT_EQ(param.expectedOutcome, matchHexAndBin(param.hex, param.bin));
}

INSTANTIATE_TEST_SUITE_P(
    UnitHexBinMatch, UnitHexBinMatch,
    testing::Values(

        TestCase{"0", "0000", true}, TestCase{"1", "0001", true},
        TestCase{"2", "0010", true}, TestCase{"3", "0011", true},
        TestCase{"4", "0100", true}, TestCase{"5", "0101", true},
        TestCase{"6", "0110", true}, TestCase{"7", "0111", true},
        TestCase{"8", "1000", true}, TestCase{"9", "1001", true},
        TestCase{"a", "1010", true}, TestCase{"b", "1011", true},
        TestCase{"c", "1100", true}, TestCase{"d", "1101", true},
        TestCase{"e", "1110", true}, TestCase{"f", "1111", true},
        TestCase{"A", "1010", true}, TestCase{"B", "1011", true},
        TestCase{"C", "1100", true}, TestCase{"D", "1101", true},
        TestCase{"E", "1110", true}, TestCase{"F", "1111", true},

        TestCase{"0123",
                 "0000"
                 "0001"
                 "0010"
                 "0011",
                 true},
        TestCase{"0123",
                 "0000"
                 "0001"
                 "0011"
                 "0010",
                 false},

        TestCase{"", "", true}, TestCase{"a", "", false},
        TestCase{"", "1", false},

        TestCase{"0", "0", true}, TestCase{"1", "1", true},
        TestCase{"2", "10", true}, TestCase{"3", "11", true},
        TestCase{"4", "100", true}, TestCase{"7", "111", true},

        TestCase{"0123",
                 "0"
                 "0001"
                 "0010"
                 "0011",
                 true}

        ),
    &UnitHexBinMatch::getTestName);

auto UnitHexBinMatch::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    const auto &param = testInfo.param;
    return std::string(param.hex) + "_" + std::string(param.bin) + "_" +
           std::to_string(param.expectedOutcome);
}

}  // namespace hex_bin_match
