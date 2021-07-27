
#include "three_steps.h"

#include <algorithm>
#include <array>
#include <cassert>

namespace dynamic_programming {

auto count_combinations_in_climbing_stairs(std::int64_t n) -> std::int64_t {

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

std::int64_t count_combinations_recursion(
        std::int64_t size,
        std::unordered_map<std::int64_t, std::int64_t> *memo) {

    assert(memo != nullptr);

    if (size < 0) return 0;
    if (size == 0) return 1;

    auto it = memo->find(size);
    if (it != memo->end()) {
        return it->second;
    }

    auto result =
            count_combinations_recursion(size - 1, memo)
            + count_combinations_recursion(size - 2, memo)
            + count_combinations_recursion(size - 3, memo);

    memo->emplace(size, result);
    return result;
}

} // namespace

auto count_combinations_in_climbing_stairs_recursive(std::int64_t n) -> std::int64_t {
    std::unordered_map<std::int64_t, std::int64_t> memo;
    memo.reserve(n);
    return count_combinations_recursion(n, &memo);
}

} // namespace dynamic_programming