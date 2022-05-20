cmake_minimum_required(VERSION 3.5)

project(openGLStudy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(openGLStudy main.cpp)
target_link_libraries(${PROJECT_NAME} GL dl  glfw)

