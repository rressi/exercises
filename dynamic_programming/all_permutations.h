#pragma once

#include <string>
#include <unordered_set>

namespace dp {

using AllPermutations = std::unordered_set<std::string>;

auto extractAllPermutations(const std::string &input) -> AllPermutations;

}  // namespace dp
