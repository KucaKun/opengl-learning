
set(BENCHMARKS)

function(i_bench_100 file_name_without_extension)
    add_executable(${file_name_without_extension}
        src/benchmarks/${file_name_without_extension}.cpp
        ${SOURCES}
    )
    set(BENCHMARKS ${BENCHMARKS} ${file_name_without_extension})
    target_link_libraries(${file_name_without_extension} benchmark::benchmark ${CMAKE_CURRENT_SOURCE_DIR}/glew/lib/Release/x64/glew32s.lib glfw ${OPENGL_LIBRARIES} imgui)
endfunction()