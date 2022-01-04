option(BENCHMARK_ENABLE_GTEST_TESTS "Enable building the unit tests which depend on gtest" OFF)
option(BENCHMARK_ENABLE_TESTING "Enable building the unit tests which depend on gtest" OFF)
add_subdirectory(benchmark)

option(INSTALL_GTEST "Enable installation of googletest." OFF)
add_subdirectory(googletest)

function(addZlib)
    file(READ "zlib/CMakeLists.txt" ZLIB_CMAKELISTS_ORIGINAL)
    file(READ "zlib/zconf.h" ZLIB_CONF_ORIGINAL)
    string(REGEX REPLACE
        "(add_executable|add_test|set_target_properties|target_link_libraries)[(](example|example64|minigzip|minigzip64) [^)]+[)]"
        ""
        ZLIB_CMAKELISTS_PATCHED
        "${ZLIB_CMAKELISTS_ORIGINAL}")
    file(WRITE "zlib/CMakeLists.txt" "${ZLIB_CMAKELISTS_PATCHED}")
    file(REMOVE "zlib/zconf.h")

    add_subdirectory(zlib)

    file(WRITE "zlib/CMakeLists.txt" "${ZLIB_CMAKELISTS_ORIGINAL}")
    file(WRITE "zlib/zconf.h" "${ZLIB_CONF_ORIGINAL}")
    
    foreach(target zlib zlibstatic)
        target_include_directories(
            "${target}"
            PUBLIC
                "${CMAKE_CURRENT_LIST_DIR}"
        )
    endforeach()
endfunction()
addZlib()

option(protobuf_BUILD_TESTS "Build tests of Protobuf" OFF)
if(MSVC)
    option(protobuf_BUILD_SHARED_LIBS "Build Shared Libraries" ON)
endif()
add_subdirectory(protobuf/cmake)
