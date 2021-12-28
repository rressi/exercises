#pragma once

#include <optional>
#include <vector>

namespace sieve_of_eratosthenes {

using Number = unsigned int;

template <class T>
using Opt = std::optional<T>;

auto findPrimeNumbers(Number maxNumber, Opt<unsigned> maxThreads = {})
    -> std::vector<Number>;

}  // namespace sieve_of_eratosthenes