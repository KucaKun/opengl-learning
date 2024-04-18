cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

project(opengl-learning)

add_executable(main src/main.cpp)
add_subdirectory(glfw)

target_link_libraries(main glfw)
install(TARGETS main DESTINATION __)