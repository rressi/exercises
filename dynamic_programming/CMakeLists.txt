
add_executable(

        test_dynamic_programming

        all_permutations.h
        all_permutations.cpp
        all_permutations.t.cpp

        all_subsets.h
        all_subsets.t.cpp

        edit_distance.cpp
        edit_distance.h
        edit_distance.t.cpp

        robot_navigator.cpp
        robot_navigator.h
        robot_navigator.t.cpp

        three_steps.cpp
        three_steps.h
        three_steps.t.cpp

)

target_link_libraries(test_dynamic_programming gtest_main)

include(GoogleTest)
gtest_discover_tests(test_dynamic_programming)
