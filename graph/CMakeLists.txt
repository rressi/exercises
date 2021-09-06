
add_executable(

        test_graph
        graph.cpp
        graph.h
        graph.t.cpp

)

target_link_libraries(test_graph gtest_main)
