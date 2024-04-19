#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "error_handling.hpp"
#include "shaders.hpp"
#define COUNT 3

GLFWwindow* initialize_gl_context() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        return nullptr;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return nullptr;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();

    glfwSwapInterval(1);
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(error, nullptr);
    std::cout << glGetString(GL_VERSION) << std::endl;
    return window;
}

int main(void) {
    GLFWwindow* window = initialize_gl_context();
    float positions[]  = {
        // 0
        -0.5f,
        -0.5f,
        // 1
        0.5f,
        -0.5f,
        // 2
        0.5f,
        0.5f,
        // 3
        -0.5f,
        0.5f,
    };
    unsigned int indices[]{0, 1, 2, 2, 3, 0};
    unsigned int vao; // vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Prepare buffer
    unsigned int buffer_id;
    glGenBuffers(1, &buffer_id); // generate empty buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id); // has to be bound to use
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW); // fill buffer with data

    // Prepare attributes
    glVertexAttribPointer(
        0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // describe how the data in the buffer is structured
    glEnableVertexAttribArray(0); // enable the structuring that was set
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinding the buffer

    // Prepare index buffer
    unsigned int ibo; // index buffer object
    glGenBuffers(1, &ibo); // generate empty buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // has to be bound to use
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW); // fill buffer with data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbinding ibo

    // load shaders
    ShaderSources sources = read_sources_from_file("basic.glsl");
    unsigned int shader   = create_shader(sources.vertex_shader, sources.fragment_shader);
    glUseProgram(shader);

    // prepare uniforms
    int location = glGetUniformLocation(shader, "u_color");
    glUniform4f(location, 0.12, 0.2, 1.0, 1.0);

    float frame = 0;
    while (!glfwWindowShouldClose(window)) {
        // prepare frame
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao); // has to be bound to use
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // has to be bound to use

        // modifying the uniforms
        auto i = (int) frame % 144;
        glUniform4f(location, 1.0 / i, 1.0 / (i / 3.), 1.0 / (i / 2.), 1.0);


        // draw frame
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // draw index buffer
        glfwSwapBuffers(window);
        glfwPollEvents();

        // finish
        frame++;
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
