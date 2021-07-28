#pragma once

#include <set>

namespace dynamic_programming {

template<class T>
auto extractAllSubSets(const std::set<T> &source) -> std::set<std::set<T>> {

    auto results = std::set<std::set<T>>{};
    results.insert(std::set<T>());
    results.insert(source);

    for (const auto &item: source) {
        auto subset = source;
        subset.erase(item);
        if (results.count(subset) == 0) {
            auto allSubsets = extractAllSubSets(subset);
            results.insert(allSubsets.begin(), allSubsets.end());
        }
    }

    return results;
}

} // namespace dynamic_programming
