cmake_minimum_required(VERSION 3.4...3.28 FATAL_ERROR)

project(opengl-learning)

include(testing.cmake)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall")
set(CMAKE_COLOR_DIAGNOSTICS)

find_package(OpenGL REQUIRED)

include_directories(src/include)
include_directories(glm)
include_directories(src/external/include)
include_directories(glew/include)
include_directories(imgui)
include_directories(glfw/include)

set(SOURCES
    src/vertex_buffer.cpp
    src/index_buffer.cpp
    src/vertex_array.cpp
    src/renderer.cpp
    src/shader.cpp
    src/uniform.cpp
    src/texture.cpp
    src/window.cpp
    src/object.cpp
    src/point.cpp
    src/random_particle.cpp
    src/object_manager.cpp
    src/examples/point_scene.cpp
    src/examples/raw_scene.cpp

    src/examples/milion_points_scene.cpp
    src/external/stb_image.cpp)

add_executable(main
    src/main.cpp ${SOURCES}
)

add_subdirectory(googletest)

test_me_motherfucker(vertex_buffer_layout_test)
test_me_motherfucker(shader_compile_test)

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/src/shaders"
    $<TARGET_FILE_DIR:main>)

add_custom_command(TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/res"
    $<TARGET_FILE_DIR:main>)

link_directories(glfw)
add_subdirectory(glfw)

link_directories(imgui)
add_subdirectory(imgui)

add_compile_definitions(GLEW_STATIC)

target_link_libraries(main ${CMAKE_CURRENT_SOURCE_DIR}/glew/lib/Release/x64/glew32s.lib)
target_link_libraries(main glfw)
target_link_libraries(main ${OPENGL_LIBRARIES})
target_link_libraries(main imgui)

install(TARGETS main DESTINATION __)
