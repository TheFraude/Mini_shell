cmake_minimum_required(VERSION 3.27)
project(untitled C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled
        my_string.c
        my_string.h
        Squelette.c
        shell_function.c
        shell_function.h
)

# Add a custom command to compile with gcc
add_custom_target(run
        COMMAND gcc -ansi -Wall -o mini_shell untitled
        DEPENDS untitled
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)