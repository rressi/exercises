
add_executable(

        test_reverse_concatenated_list
        reverse_concatenated_list.cpp
        reverse_concatenated_list.h
        reverse_concatenated_list.t.cpp

        )

target_link_libraries(test_reverse_concatenated_list gtest_main)
