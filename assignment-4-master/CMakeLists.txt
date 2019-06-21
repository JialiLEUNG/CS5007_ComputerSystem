cmake_minimum_required(VERSION 3.14)
project(lecture-4-master)

set(CMAKE_CXX_STANDARD 14)
include_directories(.)

add_executable(lecture-4-master
        manage_threads.c
#        test_thread.c
        )