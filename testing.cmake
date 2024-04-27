
set(TESTS)

function(test_me_motherfucker test_name_without_extension)
    add_executable(${test_name_without_extension}
        src/tests/${test_name_without_extension}.cpp
        ${SOURCES}
    )
    add_test(NAME ${test_name_without_extension} COMMAND ${test_name_without_extension})
    set(TESTS ${TESTS} ${test_name_without_extension})
    target_link_libraries(${test_name_without_extension} gtest gtest_main ${CMAKE_CURRENT_SOURCE_DIR}/glew/lib/Release/x64/glew32s.lib glfw ${OPENGL_LIBRARIES} imgui)
endfunction()