cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

project(opengl-learning)

add_executable(main src/main.cpp)
add_subdirectory(glfw)
add_subdirectory(glew)
find_package(OpenGL REQUIRED)

target_link_libraries(main glfw)
target_link_libraries(main ${OPENGL_LIBRARIES})

install(TARGETS main DESTINATION __)