cmake_minimum_required(VERSION 3.12)
project(round_robin_scheduler VERSION 0.1.0 LANGUAGES C)

include_directories(include)

add_executable(round_robin_scheduler src/main.c src/circular_queue.c src/task.c)