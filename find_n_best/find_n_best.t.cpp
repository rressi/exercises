
#include "find_n_best.h"

#include <gtest/gtest.h>

#include <list>
#include <random>
#include <string>


namespace find_n_best {

template<class Container>
class UnitFindNBest : public ::testing::Test {

protected:
    using Value = typename Container::value_type;

    auto generateValues(std::size_t numValues) -> Container;
};

using ContainerTypes = ::testing::Types<

        std::vector<int>,
        std::list<int>,
        std::deque<int>,

        std::vector<std::uint64_t>,
        std::list<std::uint64_t>,
        std::deque<std::uint64_t>,

        std::vector<std::string>,
        std::list<std::string>,
        std::deque<std::string>

>;
TYPED_TEST_SUITE(UnitFindNBest, ContainerTypes);

TYPED_TEST(UnitFindNBest, testFindNBest) {
    constexpr auto NUM_VALUES = 10'000;
    constexpr auto NUM_BIGGEST_VALUES = 100;

    using Container = TypeParam;
    using Value = typename Container::value_type;

    auto values = this->generateValues(NUM_VALUES);
    auto actualBiggestValues = findBiggestItems(values, NUM_BIGGEST_VALUES);
    EXPECT_EQ(NUM_BIGGEST_VALUES, actualBiggestValues.size());

    auto expectedBiggestValues = std::vector<Value>(values.begin(), values.end());
    std::sort(expectedBiggestValues.begin(), expectedBiggestValues.end(), std::greater<Value>());
    expectedBiggestValues.resize(NUM_BIGGEST_VALUES);
    EXPECT_EQ(NUM_BIGGEST_VALUES, expectedBiggestValues.size());

    EXPECT_EQ(expectedBiggestValues, actualBiggestValues);
}

TYPED_TEST(UnitFindNBest, testFindNBestWithHeap) {
    constexpr auto NUM_VALUES = 10'000;
    constexpr auto NUM_BIGGEST_VALUES = 100;

    using Container = TypeParam;
    using Value = typename Container::value_type;

    auto values = this->generateValues(NUM_VALUES);
    auto actualBiggestValues = findBiggestItemsWithHeap(values, NUM_BIGGEST_VALUES);
    EXPECT_EQ(NUM_BIGGEST_VALUES, actualBiggestValues.size());

    auto expectedBiggestValues = std::vector<Value>(values.begin(), values.end());
    std::sort(expectedBiggestValues.begin(), expectedBiggestValues.end(), std::greater<Value>());
    expectedBiggestValues.resize(NUM_BIGGEST_VALUES);
    EXPECT_EQ(NUM_BIGGEST_VALUES, expectedBiggestValues.size());

    EXPECT_EQ(expectedBiggestValues, actualBiggestValues);
}


using RandomGenerator = std::mt19937_64;

template<class X>
auto generateValue(RandomGenerator *randomGenerator) -> X {
    return X(randomGenerator->operator()());
}

template<>
auto generateValue<std::string>(RandomGenerator *randomGenerator) -> std::string {
    auto x = std::string();

    auto size = std::size_t(randomGenerator->operator()() % 20);
    for (auto i = 0U; i < size; i++) {
        auto ch = char('A' + randomGenerator->operator()() % ('Z' - 'A' + 1));
        x.push_back(ch);
    }

    return x;
}

template<class Container>
auto UnitFindNBest<Container>::generateValues(std::size_t numValues) -> Container {
    auto values = Container();

    auto randomGenerator = RandomGenerator(4242);

    for (auto i = 0U; i < numValues; i++) {
        values.push_back(generateValue<Value>(&randomGenerator));
    }

    return values;
}

} // namespace find_n_best
