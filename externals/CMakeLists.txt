option(BENCHMARK_ENABLE_GTEST_TESTS "Enable building the unit tests which depend on gtest" OFF)
option(BENCHMARK_ENABLE_TESTING "Enable building the unit tests which depend on gtest" OFF)
add_subdirectory(benchmark)

option(INSTALL_GTEST "Enable installation of googletest." OFF)
add_subdirectory(googletest)

if(NOT MSVC)
    option(protobuf_BUILD_TESTS "Build tests of Protobuf" OFF)
    add_subdirectory(protobuf/cmake)
endif()
