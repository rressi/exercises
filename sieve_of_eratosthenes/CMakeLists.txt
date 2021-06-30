
add_executable(

        test_sieve_of_eratosthenes
        sieve_of_eratosthenes.h
        sieve_of_eratosthenes.cpp
        sieve_of_eratosthenes.t.cpp

        )

target_link_libraries(test_sieve_of_eratosthenes gtest_main)

add_executable(
        bench_sieve_of_eratosthenes
        sieve_of_eratosthenes.cpp
        sieve_of_eratosthenes.bench.cpp
        )

target_link_libraries(bench_sieve_of_eratosthenes benchmark::benchmark)
