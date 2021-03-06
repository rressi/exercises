
#include <gtest/gtest.h>

#include <functional>
#include <list>
#include <random>
#include <string>

#include "find_n_best.h"

namespace queues {

template <class Container>
class TestFindNBest : public ::testing::Test {
 protected:
  using Value = typename Container::value_type;

  template <class TargetFunction>
  void runTest(TargetFunction &&targetFunction);

  auto generateValues(std::size_t numValues) -> Container;
};

using ContainerTypes = ::testing::Types<

    std::vector<int>,  //
    std::list<int>,    //
    std::deque<int>,   //

    std::vector<std::uint64_t>,  //
    std::list<std::uint64_t>,    //
    std::deque<std::uint64_t>,   //

    std::vector<std::string>,  //
    std::list<std::string>,    //
    std::deque<std::string>    //

    >;
TYPED_TEST_SUITE(TestFindNBest, ContainerTypes);

TYPED_TEST(TestFindNBest, testFindBiggestItems) {
  using Container = TypeParam;
  using Value = typename Container::value_type;

  TestFindNBest<TypeParam>::runTest(
      [](const Container &values, std::size_t numBest) {
        return findBiggestItems(values, numBest);
      });
}

TYPED_TEST(TestFindNBest, testFindBiggestItemsWithHeap) {
  using Container = TypeParam;
  using Value = typename Container::value_type;

  TestFindNBest<TypeParam>::runTest(
      [](const Container &values, std::size_t numBest) {
        return findBiggestItemsWithHeap(values, numBest);
      });
}

template <class Container>
template <class TargetFunction>
void TestFindNBest<Container>::runTest(TargetFunction &&targetFunction) {
  constexpr auto NUM_VALUES = 10'000;
  constexpr auto NUM_BIGGEST_VALUES = 100;

  using Value = typename Container::value_type;

  auto values = generateValues(NUM_VALUES);
  auto actualBiggestValues = targetFunction(values, NUM_BIGGEST_VALUES);
  EXPECT_EQ(NUM_BIGGEST_VALUES, actualBiggestValues.size());

  auto expectedBiggestValues = std::vector<Value>(values.begin(), values.end());
  std::sort(expectedBiggestValues.begin(), expectedBiggestValues.end(),
            std::greater<Value>());
  expectedBiggestValues.resize(NUM_BIGGEST_VALUES);
  EXPECT_EQ(NUM_BIGGEST_VALUES, expectedBiggestValues.size());

  EXPECT_EQ(expectedBiggestValues, actualBiggestValues);
}

using RandomGenerator = std::mt19937_64;

template <class X>
auto generateValue(RandomGenerator *randomGenerator) -> X {
  return X(randomGenerator->operator()());
}

template <>
auto generateValue<std::string>(RandomGenerator *randomGenerator)
    -> std::string {
  auto x = std::string();

  auto size = std::size_t(randomGenerator->operator()() % 20);
  for (auto i = 0U; i < size; i++) {
    auto ch = char('A' + randomGenerator->operator()() % ('Z' - 'A' + 1));
    x.push_back(ch);
  }

  return x;
}

template <class Container>
auto TestFindNBest<Container>::generateValues(std::size_t numValues)
    -> Container {
  auto values = Container();

  auto randomGenerator = RandomGenerator(4242);

  for (auto i = 0U; i < numValues; i++) {
    values.push_back(generateValue<Value>(&randomGenerator));
  }

  return values;
}

}  // namespace queues
