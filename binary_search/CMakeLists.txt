add_executable(
    test_binary_search

    magic_key.cpp
    magic_key.h
    magic_key.t.cpp
)

target_link_libraries(
    test_binary_search
    PRIVATE
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_binary_search)
