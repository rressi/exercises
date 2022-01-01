option(BENCHMARK_ENABLE_GTEST_TESTS "Enable building the unit tests which depend on gtest" OFF)
option(BENCHMARK_ENABLE_TESTING "Enable building the unit tests which depend on gtest" OFF)
add_subdirectory(benchmark)

option(INSTALL_GTEST "Enable installation of googletest." OFF)
add_subdirectory(googletest)

option(protobuf_BUILD_TESTS "Build tests of Protobuf" OFF)
if(MSVC)
    option(protobuf_BUILD_SHARED_LIBS "Build Shared Libraries" ON)
endif()
add_subdirectory(protobuf/cmake)
