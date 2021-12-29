
add_executable(

        test_find_n_best
        find_n_best.h
        find_n_best.t.cpp

        )

target_link_libraries(test_find_n_best gtest_main)

include(GoogleTest)
gtest_discover_tests(test_find_n_best)
