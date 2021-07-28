
add_executable(

        dynamic_programming

        all_subsets.h
        all_subsets.t.cpp

        robot_navigator.cpp
        robot_navigator.h
        robot_navigator.t.cpp

        three_steps.cpp
        three_steps.h
        three_steps.t.cpp

)

target_link_libraries(dynamic_programming gtest_main)
