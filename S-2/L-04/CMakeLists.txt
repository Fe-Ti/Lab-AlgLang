# Copyright 2021 Fe-Ti <btm.007@mail.ru>

cmake_minimum_required(VERSION 3.4)

project(exceptions_OOP)

set(SOURCE_XDEMO src/exceptions-demo.cpp)

include_directories(lib-cx)

add_executable(demo ${SOURCE_XDEMO})
add_subdirectory(lib-cx)

target_link_libraries(demo lib_cx)


