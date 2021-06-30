
#include "sieve_of_eratosthenes.h"

#include <benchmark/benchmark.h>


namespace {

template<unsigned maxThreads>
void BM_FindPrimeNumbers(benchmark::State &state) {
    auto maxNumber = sieve_of_eratosthenes::Number(state.range(0));
    for (auto _ : state) {
        sieve_of_eratosthenes::findPrimeNumbers(maxNumber, maxThreads);
    }
    state.SetComplexityN(state.range(0));
}

} // namespace

BENCHMARK_TEMPLATE(BM_FindPrimeNumbers, 1)->RangeMultiplier(10)->Range(1'000, 10'000'000)->Complexity();
BENCHMARK_TEMPLATE(BM_FindPrimeNumbers, 2)->RangeMultiplier(10)->Range(1'000, 10'000'000)->Complexity();
BENCHMARK_TEMPLATE(BM_FindPrimeNumbers, 4)->RangeMultiplier(10)->Range(1'000, 10'000'000)->Complexity();
BENCHMARK_TEMPLATE(BM_FindPrimeNumbers, 8)->RangeMultiplier(10)->Range(1'000, 10'000'000)->Complexity();
BENCHMARK_TEMPLATE(BM_FindPrimeNumbers, 16)->RangeMultiplier(10)->Range(1'000, 10'000'000)->Complexity();

BENCHMARK_MAIN();
