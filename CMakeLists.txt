cmake_minimum_required(VERSION 3.10)
project(blink)

set(BLINK_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_definitions(-DSPDLOG_COMPILED_LIB=1)

set(GCC_COVERAGE_COMPILE_FLAGS --coverage -O0 -fprofile-arcs -ftest-coverage 
    -fno-elide-constructors -fno-inline)
set(GCC_COVERAGE_LINK_FLAGS "-lgcov")

option(ENABLE_TESTS "Build unit tests" OFF)
option(ENABLE_COVERAGE "Enable code coverage" OFF)

if (ENABLE_COVERAGE)
    message("-- Triggering build with coverage support")
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
    string(REPLACE "-O3" "" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
else()
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O1")
endif()

if(ENABLE_TESTS)
    enable_testing()
endif()

add_subdirectory(3rdparty)
add_subdirectory(src/blink)
add_subdirectory(sandbox)