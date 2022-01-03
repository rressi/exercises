#include <gtest/gtest.h>

#include <ios>

#include "magic_key.h"

namespace binary_search {
namespace {

using InputValues = std::vector<int>;
using ExpectedOutcome = bool;

struct TestCase {
    InputValues inputValues{};
    ExpectedOutcome expectedOutcome{};
};

}  // namespace

class TestMagicKey : public ::testing::TestWithParam<TestCase> {
   public:
    static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
        -> std::string;
};

TEST_P(TestMagicKey, testHasMagicKey) {
    const auto &inputValues = TestMagicKey::GetParam().inputValues;

    auto actualOutcome = hasMagicKey(inputValues);

    const auto &expectedOutcome = TestMagicKey::GetParam().expectedOutcome;
    EXPECT_EQ(expectedOutcome, actualOutcome);
}

INSTANTIATE_TEST_SUITE_P(
    TestMagicKey, TestMagicKey,
    testing::Values(

        TestCase{InputValues{}, ExpectedOutcome{false}},

        TestCase{InputValues{0}, ExpectedOutcome{true}},
        TestCase{InputValues{1}, ExpectedOutcome{false}},

        TestCase{InputValues{0, 1}, ExpectedOutcome{true}},
        TestCase{InputValues{0, 2}, ExpectedOutcome{true}},
        TestCase{InputValues{1, 2}, ExpectedOutcome{false}},

        TestCase{InputValues{0, 1, 2}, ExpectedOutcome{true}},
        TestCase{InputValues{0, 2, 3}, ExpectedOutcome{true}},
        TestCase{InputValues{-1, 0, 2}, ExpectedOutcome{true}},
        TestCase{InputValues{1, 3, 4}, ExpectedOutcome{false}},
        TestCase{InputValues{1, 2, 3}, ExpectedOutcome{false}},

        TestCase{InputValues{0, 1, 2, 3}, ExpectedOutcome{true}},
        TestCase{InputValues{1, 1, 3, 4}, ExpectedOutcome{true}},
        TestCase{InputValues{0, 2, 3, 4}, ExpectedOutcome{true}},
        TestCase{InputValues{-2, -1, 1, 3}, ExpectedOutcome{true}},
        TestCase{InputValues{1, 2, 3, 4}, ExpectedOutcome{false}},

        TestCase{InputValues{0, 1, 2, 3, 4}, ExpectedOutcome{true}},
        TestCase{InputValues{0, 1, 3, 4, 5}, ExpectedOutcome{true}},
        TestCase{InputValues{0, 2, 3, 4, 5}, ExpectedOutcome{true}},
        TestCase{InputValues{-2, -1, 0, 3, 5}, ExpectedOutcome{true}},
        TestCase{InputValues{-2, -1, 0, 2, 4}, ExpectedOutcome{true}}

        ),
    &TestMagicKey::getTestName);

auto TestMagicKey::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
    auto name = std::string("case");

    for (auto &value : testInfo.param.inputValues) {
        auto item = std::to_string(value);
        if (item.front() == '-') {
            item.front() = ' m';
        }
        name.append("_").append(item);
    }

    return name;
}

namespace {

template <class T>
auto vactorToString(const std::vector<T> &values) -> std::string {
    std::stringstream buf;
    buf << "[";
    auto sep = "";
    for (const auto &value : values) {
        buf << sep << value;
        sep = ", ";
    }
    buf << "]";
    return buf.str();
}

auto operator<<(std::ostream &out, const TestCase &testCase) -> std::ostream & {
    out << "{ \"inputValues\": \"" << vactorToString(testCase.inputValues)
        << ", \"expectedOutcome\": \"" << std::boolalpha
        << testCase.expectedOutcome << "\"}";
    return out;
}

}  // namespace
}  // namespace binary_search