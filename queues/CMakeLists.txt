
add_executable(
    test_queues

    find_n_best.h
    find_n_best.t.cpp
)

target_link_libraries(
    test_queues
    PRIVATE
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_queues)
