cmake_minimum_required(VERSION 3.26)
project(gestion_processus C)

set(CMAKE_C_STANDARD 11)

add_executable(gestion_processus main.c
        processus.h

        processus.c
        processus.c)
