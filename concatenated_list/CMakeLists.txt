
add_executable(

        test_concatenated_list
        concatenated_list.cpp
        concatenated_list.h
        concatenated_list.t.cpp

        )

target_link_libraries(test_concatenated_list gtest_main)
