
#include "sieve_of_eratosthenes.h"

namespace sieve_of_eratosthenes {

auto findPrimeNumbers(Number maxNumber) -> std::vector<Number> {

    auto foundPrimeNumbers = std::vector<Number>();

    std::vector<bool> sieve;
    sieve.resize(maxNumber + 1);

    for (auto x = 2; x <= maxNumber; x++) {
        if (!sieve[x]) {
            foundPrimeNumbers.emplace_back(x);
            for (auto multiplierOfX = (x + x); multiplierOfX <= maxNumber; multiplierOfX += x) {
                sieve[multiplierOfX] = true;
            }
        }
    }

    return foundPrimeNumbers;
}

} // namespace sieve_of_eratosthenes