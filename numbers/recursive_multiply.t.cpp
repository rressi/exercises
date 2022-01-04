
#include <gtest/gtest.h>

#include <tuple>

#include "recursive_multiply.h"

namespace numbers {
namespace {

using Multiplicand = std::uint32_t;
using TestCase = std::tuple<Multiplicand, Multiplicand>;

}  // namespace

class TestRecursiveMultiply : public ::testing::TestWithParam<TestCase> {
 public:
  static auto getTestName(const ::testing::TestParamInfo<TestCase> &testInfo)
      -> std::string;
};

TEST_P(TestRecursiveMultiply, testRecursiveMultiply) {
  auto [a, b] = TestRecursiveMultiply::GetParam();

  auto actualResult = recursiveMultiply(a, b);

  auto expectedResult = std::uint64_t(a) * std::uint64_t(b);
  EXPECT_EQ(expectedResult, actualResult);
}

INSTANTIATE_TEST_SUITE_P(FromZeroToTen, TestRecursiveMultiply,
                         ::testing::Combine(::testing::Range(0U, 10U),
                                            ::testing::Range(0U, 10U)),
                         &TestRecursiveMultiply::getTestName);
INSTANTIATE_TEST_SUITE_P(EdgeCases, TestRecursiveMultiply,
                         ::testing::Combine(::testing::Values(0U, ~0U),
                                            ::testing::Values(0U, ~0U)),
                         &TestRecursiveMultiply::getTestName);

auto TestRecursiveMultiply::getTestName(
    const ::testing::TestParamInfo<TestCase> &testInfo) -> std::string {
  auto [a, b] = testInfo.param;
  return std::to_string(a) + "_mult_" + std::to_string(b);
}

}  // namespace numbers
