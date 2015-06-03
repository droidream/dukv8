cmake_minimum_required(VERSION 3.2)
project(dukv8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include deps/duktape deps/tracey)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(dukv8
    ${SOURCE_FILES}
    deps/duktape/duktape.c
    samples/main.cpp)