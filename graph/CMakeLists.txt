
add_executable(
        test_graph

        graph.cpp
        graph.h
        graph.t.cpp
)

target_link_libraries(test_graph PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(test_graph)
