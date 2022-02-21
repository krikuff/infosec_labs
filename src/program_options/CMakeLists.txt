cmake_minimum_required(VERSION 3.22)

project(program_options)

set(HEADERS
    program_options.h
    )

set(SOURCES
    program_options.cpp
    )

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})
