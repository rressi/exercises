
add_executable(
    test_tree

    binary_tree.cpp
    binary_tree.h
    binary_tree.t.cpp

    tree.cpp
    tree.h
    tree.t.cpp
)

include(AddProtos)
add_protos(TARGET test_tree
       PROTOC_OUT_DIR "${CMAKE_CURRENT_LIST_DIR}"
       PROTOS tree.proto)

target_link_libraries(test_tree PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(test_tree)
