add_executable(
    test_binary_tree

    binary_tree.cpp
    binary_tree.h
    binary_tree.t.cpp
)

target_link_libraries(
    test_binary_tree 
    PRIVATE 
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_binary_tree)
