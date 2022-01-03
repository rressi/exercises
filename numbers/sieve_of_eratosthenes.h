#pragma once

#include <optional>
#include <vector>

namespace numbers {

using Number = unsigned int;

template <class T>
using Opt = std::optional<T>;

auto findPrimeNumbers(Number maxNumber, Opt<unsigned> maxThreads = {})
    -> std::vector<Number>;

}  // namespace numbers