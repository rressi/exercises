
add_executable(

        test_binary_tree
        binary_tree.cpp
        binary_tree.h
        binary_tree.t.cpp

        )

target_link_libraries(test_binary_tree gtest_main)
