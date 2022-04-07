cmake_minimum_required(VERSION 3.21)
project(NewProject C)

set(CMAKE_C_STANDARD 11)

add_executable(NewProject main.c twitter_create.c twitter_create.h)
