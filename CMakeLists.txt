cmake_minimum_required(VERSION 3.8)
project(my-p6-project)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)



# ---Add p6---
add_subdirectory(p6)
target_link_libraries(${PROJECT_NAME} p6::p6)


include_directories(
    src
    src/include
)

# Add all the files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*)
target_sources(${PROJECT_NAME} PRIVATE ${MY_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)