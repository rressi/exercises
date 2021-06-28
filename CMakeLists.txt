cmake_minimum_required(VERSION 3.16)
project(life++)

set(CMAKE_CXX_STANDARD 17)

option(INSTALL_GTEST "Enable installation of googletest." OFF)

add_subdirectory(edit_distance)
add_subdirectory(googletest)
add_subdirectory(hex_bin_match)
