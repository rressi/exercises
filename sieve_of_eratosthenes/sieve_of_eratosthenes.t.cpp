
#include "sieve_of_eratosthenes.h"

#include <gtest/gtest.h>

namespace sieve_of_eratosthenes {

struct TestCaseSequential {
    Number maxNumber{};
    std::vector<Number> expectedOutcome{};
};

class UnitSieveOfEratosthenesSequential : public ::testing::TestWithParam<TestCaseSequential> {
public:
    static auto getTestName(const ::testing::TestParamInfo<TestCaseSequential> &testInfo) -> std::string;
};

INSTANTIATE_TEST_SUITE_P(UnitSieveOfEratosthenesSequential,
                         UnitSieveOfEratosthenesSequential,
                         testing::Values(

                                 TestCaseSequential{10,
                                                    {2, 3, 5, 7}},

                                 TestCaseSequential{97,
                                                    {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61,
                                                     67, 71, 73, 79, 83, 89}},

                                 TestCaseSequential{100,
                                                    {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61,
                                                     67, 71, 73, 79, 83, 89, 97}},

                                 TestCaseSequential{1'000,
                                                    {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61,
                                                     67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137,
                                                     139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199,
                                                     211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277,
                                                     281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359,
                                                     367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439,
                                                     443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521,
                                                     523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607,
                                                     613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683,
                                                     691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773,
                                                     787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
                                                     877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967,
                                                     971, 977, 983, 991, 997}},

                                 TestCaseSequential{}
                         ),
                         &UnitSieveOfEratosthenesSequential::getTestName);

TEST_P(UnitSieveOfEratosthenesSequential, testSequential) {
    const auto &param = GetParam();
    constexpr auto ONE_THREAD = 1;
    EXPECT_EQ(param.expectedOutcome, findPrimeNumbers(param.maxNumber, ONE_THREAD));
}

auto UnitSieveOfEratosthenesSequential::getTestName(
        const ::testing::TestParamInfo<TestCaseSequential> &testInfo) -> std::string {

    return "maxNumber_" + std::to_string(testInfo.param.maxNumber);
}


using MaxNumber = Number;
using MaxThreads = unsigned int;
using TestCaseParallel = std::tuple<MaxNumber, MaxThreads>;

class UnitSieveOfEratosthenesParallel : public ::testing::TestWithParam<TestCaseParallel> {
public:
    static auto getTestName(const ::testing::TestParamInfo<TestCaseParallel> &testInfo) -> std::string;
};

INSTANTIATE_TEST_SUITE_P(UnitSieveOfEratosthenesParallel,
                         UnitSieveOfEratosthenesParallel,
                         ::testing::Combine(::testing::Values(1'000, 10'000, 100'000, 1'000'000),
                                            ::testing::Values(1, 2, 4, 8, 16)),
                         &UnitSieveOfEratosthenesParallel::getTestName);

TEST_P(UnitSieveOfEratosthenesParallel, testParallel) {

    const auto &param = UnitSieveOfEratosthenesParallel::GetParam();
    auto maxNumber = std::get<0>(param);

    constexpr auto ONE_THREAD = 1;
    auto expectedResults = findPrimeNumbers(maxNumber, ONE_THREAD);

    auto maxThreads = std::get<1>(param);
    auto actualResults = findPrimeNumbers(maxNumber, maxThreads);

    EXPECT_EQ(expectedResults.size(), actualResults.size());

    auto numComparableResults = int(std::min(expectedResults.size(), actualResults.size()));
    for (auto i = 0; i < numComparableResults; i++) {
        ASSERT_EQ(expectedResults[i], actualResults[i]) << "at position: " << i;
    }
}

auto UnitSieveOfEratosthenesParallel::getTestName(
        const ::testing::TestParamInfo<TestCaseParallel> &testInfo) -> std::string {

    auto maxNumber = std::get<0>(testInfo.param);
    auto maxThreads = std::get<1>(testInfo.param);
    return "maxNumber_" + std::to_string(maxNumber) + "_maxThreads_" + std::to_string(maxThreads);
}

} // namespace sieve_of_eratosthenes
