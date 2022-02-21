cmake_minimum_required(VERSION 3.22)

project(encryptor)

set(HEADERS
    general_functions.h
    )

set(SOURCES
    general_functions.cpp
    main.cpp
    )

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC program_options cyphers)
