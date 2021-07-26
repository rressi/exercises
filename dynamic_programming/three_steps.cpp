
#include "three_steps.h"

#include <vector>

namespace dynamic_programming {

auto count_combinations_in_climbing_stairs(int n) -> int {

    if (n <= 3) {
        return n;
    }

    auto dp = std::vector<int>{1, 2, 3};
    dp.reserve(n + 1);

    while (dp.size() < n) {
        auto a = dp[dp.size() - 1];
        auto b = dp[dp.size() - 2];
        auto c = dp[dp.size() - 3];
        dp.push_back(a + b + c);
    }

    return dp.back();
}

} // namespace dynamic_programming