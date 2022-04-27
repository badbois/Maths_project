cmake_minimum_required(VERSION 3.8)
project(my-p6-project)

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)



# ---Add p6---
add_subdirectory(lib/p6)
target_link_p6_library(${PROJECT_NAME})


include_directories(
    src
    src/include
)

# Add all the files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*)
target_sources(${PROJECT_NAME} PRIVATE ${MY_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)

#
#Add a post build operation to copy shaders to the output folder (where the executable is created)
#
function(copy_folder_to_the_output_folder _FOLDERPATH)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/${_FOLDERPATH}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/${_FOLDERPATH}
)
endfunction()

copy_folder_to_the_output_folder("assets")