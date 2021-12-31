include(AddProtos)

add_executable(
        test_linked_list

        node.cpp
        node.h
        node.t.cpp

        list.cpp
        list.h
)

add_protos(TARGET test_linked_list
           PROTOC_OUT_DIR "${CMAKE_CURRENT_LIST_DIR}"
           PROTOS node.proto)


target_link_libraries(
        test_linked_list 
        
        PRIVATE 
        gtest_main
        libprotobuf
)

include(GoogleTest)
gtest_discover_tests(test_linked_list)
