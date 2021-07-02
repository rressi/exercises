cmake_minimum_required(VERSION 3.16)
project(life++)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(concatenated_list)
add_subdirectory(edit_distance)
add_subdirectory(hex_bin_match)
add_subdirectory(find_n_best)
add_subdirectory(sieve_of_eratosthenes)


option(BENCHMARK_ENABLE_GTEST_TESTS "Enable building the unit tests which depend on gtest" OFF)
option(BENCHMARK_ENABLE_TESTING "Enable building the unit tests which depend on gtest" OFF)
add_subdirectory(externals/benchmark)


option(INSTALL_GTEST "Enable installation of googletest." OFF)
add_subdirectory(externals/googletest)
