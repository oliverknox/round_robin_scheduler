add_executable(test_app
    test_circular_queue.c
)

target_link_libraries(test_app
    src
    unity
)

add_test(all_tests test_app)