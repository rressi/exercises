add_executable(
    test_binary_tree

    binary_tree.cpp
    binary_tree.h
    binary_tree.t.cpp

    binary_tree_hash.cpp
    binary_tree_hash.h
    binary_tree_hash.t.cpp

    binary_tree_visit.cpp
    binary_tree_visit.h
    binary_tree_visit.t.cpp

    is_sub_tree.cpp
    is_sub_tree.h
    is_sub_tree.t.cpp
)

target_link_libraries(
    test_binary_tree 
    PRIVATE
        gtest_main
        zlibstatic
)

include(GoogleTest)
gtest_discover_tests(test_binary_tree)
