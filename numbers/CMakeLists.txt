
add_executable(
        test_numbers

        hex_bin_match.cpp
        hex_bin_match.h
        hex_bin_match.t.cpp

        recursive_multiply.cpp
        recursive_multiply.h
        
        sieve_of_eratosthenes.h
        sieve_of_eratosthenes.cpp
        sieve_of_eratosthenes.t.cpp
)

target_link_libraries(test_numbers PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(test_numbers)

add_executable(
        bench_numbers
        sieve_of_eratosthenes.cpp
        sieve_of_eratosthenes.bench.cpp
)

target_link_libraries(bench_numbers PRIVATE benchmark::benchmark)
