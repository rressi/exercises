
#include "sieve_of_eratosthenes.h"

#include <cassert>
#include <cmath>
#include <future>
#include <thread>
#include <valarray>

namespace numbers {
namespace {

auto getNumberOfCpus() -> unsigned {
    return std::thread::hardware_concurrency();
}

auto findPrimeNumbersSequentially(Number maxNumber) -> std::vector<Number> {
    auto foundPrimeNumbers = std::vector<Number>();

    std::vector<bool> sieve;
    sieve.resize(maxNumber);

    for (auto x = 2; x < maxNumber; x++) {
        if (!sieve[x]) {
            foundPrimeNumbers.emplace_back(x);
            for (auto multiplierOfX = 2 * x; multiplierOfX < maxNumber;
                 multiplierOfX += x) {
                sieve[multiplierOfX] = true;
            }
        }
    }

    return foundPrimeNumbers;
}

auto findFirstDividend(Number primeNumber, Number minNumber) {
    auto firstDividend = minNumber - (minNumber % primeNumber);
    if (firstDividend < minNumber) {
        firstDividend += primeNumber;
    }

    firstDividend = std::max(firstDividend, primeNumber * primeNumber);
    assert(firstDividend >= minNumber);
    return firstDividend;
}

auto findPrimeNumbersInRange(const std::vector<Number> &basePrimes,
                             Number minNumber, Number maxNumber)
    -> std::vector<Number> {
    assert(!basePrimes.empty());
    assert(minNumber < maxNumber);

    auto foundPrimeNumbers = std::vector<Number>();

    std::vector<bool> sieve;
    sieve.resize(maxNumber - minNumber);

    for (auto basePrime : basePrimes) {
        for (auto x = findFirstDividend(basePrime, minNumber); x < maxNumber;
             x += basePrime) {
            sieve[x - minNumber] = true;
        }
    }

    for (auto x = 0; x < sieve.size(); x++) {
        if (!sieve[x]) {
            foundPrimeNumbers.emplace_back(x + minNumber);
        }
    }

    return foundPrimeNumbers;
}

}  // namespace

auto findPrimeNumbers(Number maxNumber, Opt<unsigned> maxThreads)
    -> std::vector<Number> {
    auto numThreads = maxThreads ? maxThreads.value() : getNumberOfCpus();

    auto sequentialMaxNumbers =
        numThreads == 1 ? maxNumber : std::min(maxNumber, Number(10'000));
    if (sequentialMaxNumbers == maxNumber) {
        return findPrimeNumbersSequentially(sequentialMaxNumbers);
    }

    auto firstPrimeNumbersMax = Number(std::lround(std::sqrt(maxNumber)));
    auto firstPrimeNumbers = findPrimeNumbersSequentially(firstPrimeNumbersMax);

    auto tasks = std::vector<std::future<std::vector<Number>>>();
    tasks.resize(numThreads);

    auto partStart = firstPrimeNumbersMax;
    auto partSize = (maxNumber - partStart) / numThreads;
    for (auto &task : tasks) {
        bool isLastPart = (&task == &tasks.back());
        auto partEnd = isLastPart ? maxNumber : partStart + partSize;

        task = std::async(std::launch::async, findPrimeNumbersInRange,
                          firstPrimeNumbers, partStart, partEnd);

        partStart += partSize;
    }

    auto primeNumbers = firstPrimeNumbers;
    for (auto &task : tasks) {
        auto partResult = task.get();
        primeNumbers.insert(primeNumbers.end(), partResult.begin(),
                            partResult.end());
    }

    return primeNumbers;
}

}  // namespace numbers