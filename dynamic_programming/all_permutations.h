#pragma once

#include <set>
#include <string>

namespace dp {

template <class Container>
using AllPermutations = std::set<Container>;

auto extractAllPermutations(const std::string &input)
    -> AllPermutations<std::string>;

}  // namespace dp
