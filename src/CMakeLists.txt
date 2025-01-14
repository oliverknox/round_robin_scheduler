add_library(src STATIC 
    circular_queue.c 
    task.c
)

add_executable(round_robin_scheduler
    main.c
)

target_link_libraries(round_robin_scheduler
    src
    fort
)