add_subdirectory(binary)

add_executable(
    test_tree

    tree.cpp
    tree.h
    tree.t.cpp
)

include(AddProtos)
add_protos(
    TARGET
        test_tree
    PROTOS
        tree.proto
)

target_link_libraries(
    test_tree 
    PRIVATE 
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_tree)
