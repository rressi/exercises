cmake_minimum_required(VERSION 3.16)
project(life++)

set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

enable_testing()

add_subdirectory(externals)

add_subdirectory(binary_search)
add_subdirectory(dynamic_programming)
add_subdirectory(graph)
add_subdirectory(linked_list)
add_subdirectory(numbers)
add_subdirectory(queues)
add_subdirectory(tree)
