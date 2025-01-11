enable_testing()

add_library(unity STATIC ../libs/unity/unity.c)
target_include_directories(unity PUBLIC ../libs/unity)

add_library(core STATIC ../src/circular_queue.c ../src/task.c)
target_include_directories(core PUBLIC ../include)

add_executable(test_round_robin_scheduler test_circular_queue.c)
target_link_libraries(test_round_robin_scheduler unity core)

# Register tests
add_test(NAME AllTests COMMAND test_round_robin_scheduler)