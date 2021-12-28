#pragma once

#include <cstdint>
#include <set>
#include <vector>

namespace dynamic_programming {

template <class T>
auto extractAllSubSets(const std::set<T> &source) -> std::set<std::set<T>> {
    if (source.size() > 64) {
        throw std::runtime_error("the source set is too big");
    }

    auto results = std::set<std::set<T>>();

    auto candidates = std::vector<T>(source.begin(), source.end());
    auto max = std::uint64_t(1) << source.size();
    for (auto mask = std::uint64_t(0); mask < max; mask++) {
        auto subset = std::set<T>();
        for (auto i = 0U; i < candidates.size(); i++) {
            if (mask & 1U << i) {
                subset.insert(candidates[i]);
            }
        }

        results.insert(std::move(subset));
    }

    return results;
}

}  // namespace dynamic_programming
