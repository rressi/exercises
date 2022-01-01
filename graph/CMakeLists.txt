
add_executable(
        test_graph

        graph.cpp
        graph.h
        graph.t.cpp
)

include(AddProtos)
add_protos(TARGET test_graph
           PROTOC_OUT_DIR "${CMAKE_CURRENT_LIST_DIR}"
           PROTOS graph.proto)

target_link_libraries(test_graph PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(test_graph)
