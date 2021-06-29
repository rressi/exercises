
add_executable(sieve_of_eratosthenes

        sieve_of_eratosthenes.cpp
        sieve_of_eratosthenes.t.cpp

        )

target_link_libraries(sieve_of_eratosthenes gtest_main)
