
add_executable(
        test_numbers

        sieve_of_eratosthenes.h
        sieve_of_eratosthenes.cpp
        sieve_of_eratosthenes.t.cpp
)

target_link_libraries(test_numbers gtest_main)

include(GoogleTest)
gtest_discover_tests(test_numbers)

add_executable(
        bench_numbers
        sieve_of_eratosthenes.cpp
        sieve_of_eratosthenes.bench.cpp
)

target_link_libraries(test_numbers benchmark::benchmark)
