add_executable(
    test_linked_list

    node.h
    node_iterator.h

    list.cpp
    list.h
    list.t.cpp
)

include(AddProtos)
add_protos(
    TARGET
        test_linked_list
    PROTOS
        node.proto
)

target_link_libraries(
    test_linked_list 
    PRIVATE 
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_linked_list)
