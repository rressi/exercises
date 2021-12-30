
add_executable(

        test_linked_list
        linked_list.cpp
        linked_list.h
        linked_list.t.cpp

        )

target_link_libraries(test_linked_list gtest_main)

include(GoogleTest)
gtest_discover_tests(test_linked_list)
