add_executable(
    test_graph

    color.cpp
    color.h

    graph.cpp
    graph.h

    has_path.cpp
    has_path.h
    has_path.t.cpp
)

target_link_libraries(
    test_graph
    PRIVATE
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_graph)
