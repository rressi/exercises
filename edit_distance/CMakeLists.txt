
add_executable(test_edit_distance

        edit_distance.cpp
        edit_distance.t.cpp

        )

target_link_libraries(test_edit_distance gtest_main)
