cmake_minimum_required(VERSION 3.12)
project(round_robin_scheduler VERSION 0.1.0 LANGUAGES C)

add_library(core STATIC 
    src/circular_queue.c 
    src/task.c
)
link_libraries(core)

include_directories(include)

add_executable(round_robin_scheduler 
    src/main.c 
    src/circular_queue.c 
    src/task.c
)

enable_testing()

add_executable(test_round_robin_scheduler
    tests/test_circular_queue.c
)

add_library(unity STATIC libs/unity/src/unity.c)
target_include_directories(unity PUBLIC libs/unity/src)

target_link_libraries(test_round_robin_scheduler unity)

add_test(NAME RunTests COMMAND test_round_robin_scheduler)
