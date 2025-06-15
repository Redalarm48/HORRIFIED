cmake_minimum_required(VERSION 3.10)

project(Horrified)

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "main.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})