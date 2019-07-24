cmake_minimum_required(VERSION 2.8)

project(cli_interp)

include_directories(include)
include_directories(source)

add_executable(${PROJECT_NAME}
    source/main.cpp

    source/interpreter.cpp
    include/interpreter.h

    source/instruction.cpp
    include/instruction.h

    source/lexer.cpp
    include/lexer.h

    source/state.cpp
    include/state.h
)
