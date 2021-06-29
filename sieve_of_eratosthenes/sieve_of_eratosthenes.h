#pragma once

#include <vector>

namespace sieve_of_eratosthenes {

using Number = unsigned int;

auto findPrimeNumbers(Number maxNumber) -> std::vector<Number>;

} // namespace sieve_of_eratosthenes