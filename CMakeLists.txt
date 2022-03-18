cmake_minimum_required(VERSION 3.8)
project(my-p6-project)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
# ---Add p6---
add_subdirectory(p6)
target_link_libraries(${PROJECT_NAME} p6::p6)