cmake_minimum_required(VERSION 3.12)
project(round_robin_scheduler VERSION 0.1.0 LANGUAGES C)

set(TARGET_GROUP debug CACHE STRING "Group to build")

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(lib)

if(TARGET_GROUP STREQUAL test)
    include(CTest)
    add_subdirectory(test)
endif()