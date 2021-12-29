
add_executable(

        test_hex_bin_match
        hex_bin_match.cpp
        hex_bin_match.h
        hex_bin_match.t.cpp

        )

target_link_libraries(test_hex_bin_match gtest_main)


include(GoogleTest)
gtest_discover_tests(test_hex_bin_match)
