cmake_minimum_required(VERSION 3.24)
project(cal C)

set(CMAKE_C_STANDARD 11)

add_executable(cal caltrain-runner.c caltrain.c)
