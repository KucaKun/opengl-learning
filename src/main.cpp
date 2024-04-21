#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "error_handling.hpp"
#include "index_buffer.hpp"
#include "shaders.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"

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

    VertexArray va;

    VertexBuffer vb(positions, 4 * 2 * sizeof(float));

    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2);

    va.add_buffer(vb, layout);

    IndexBuffer ib(indices, 6);

    Shader shader("basic.glsl");
    shader.bind();

    shader.set_uniform<float>("u_color", {0.1f, 0.2f, 0.3f, 0.4f});

    float frame = 0;
    while (!glfwWindowShouldClose(window)) {
        // prepare frame
        glClear(GL_COLOR_BUFFER_BIT);

        va.bind();
        ib.bind();

        // modifying the uniforms
        auto i = (int) frame % 144;
        shader.set_uniform<float>("u_color", {1.0f / i, 1.0f / (i / 3.f), 1.0f / (i / 2.f), 1.0f});

        // draw frame
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // draw index buffer
        glfwSwapBuffers(window);
        glfwPollEvents();

        // finish
        frame++;
    }
    shader.unbind();
    glfwTerminate();
    return 0;
}
