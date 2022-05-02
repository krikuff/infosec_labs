cmake_minimum_required(VERSION 3.22)

project(cyphers)

set(HEADERS
    magic_square_cypher.h
    )

set(SOURCES
    magic_square_cypher.cpp
    )

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})
