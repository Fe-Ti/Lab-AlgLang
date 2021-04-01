# Copyright 2021 Fe-Ti <btm.007@mail.ru>

cmake_minimum_required(VERSION 3.4)

project(lib_cx)

set(LIB_SRC custom-exception.cpp)

add_library(lib_cx ${LIB_SRC})
