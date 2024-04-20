cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

project(opengl-learning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall ")

include_directories(src/include)

add_executable(main src/main.cpp src/vertex_buffer.cpp src/index_buffer.cpp src/renderer.cpp)

add_subdirectory(glfw)

find_package(OpenGL REQUIRED)

add_compile_definitions(GLEW_STATIC)
include_directories(glew/include)
target_link_libraries(main ${CMAKE_CURRENT_SOURCE_DIR}/glew/lib/Release/x64/glew32s.lib)

target_link_libraries(main glfw)
target_link_libraries(main ${OPENGL_LIBRARIES})

install(TARGETS main DESTINATION __)

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders"
        $<TARGET_FILE_DIR:main>)