
#include "three_steps.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <unordered_map>

namespace dp {

auto countCombinationsInClimbingStairs(std::int64_t n) -> std::int64_t {
  if (n < 0) {
    return 0;
  }

  auto dp = std::array<std::int64_t, 4>{1, 0, 0, 0};
  while (n > 0) {
    std::move(dp.begin(), dp.begin() + 3, dp.begin() + 1);
    dp[0] = dp[1] + dp[2] + dp[3];
    n--;
  }

  return dp[0];
}

namespace {

auto countCombinationsRecursion(
    std::int64_t size, std::unordered_map<std::int64_t, std::int64_t> *memo)
    -> std::int64_t {
  assert(memo != nullptr);

  if (size < 0) return 0;
  if (size == 0) return 1;

  auto it = memo->find(size);
  if (it != memo->end()) {
    return it->second;
  }

  auto result = countCombinationsRecursion(size - 1, memo) +
                countCombinationsRecursion(size - 2, memo) +
                countCombinationsRecursion(size - 3, memo);

  memo->emplace(size, result);
  return result;
}

}  // namespace

auto countCombinationsInClimbingStairsRecursive(std::int64_t n)
    -> std::int64_t {
  if (n < 0) {
    return 0;
  }

  std::unordered_map<std::int64_t, std::int64_t> memo;
  memo.reserve(n);
  return countCombinationsRecursion(n, &memo);
}

}  // namespace dp