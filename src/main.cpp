#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shaders.hpp"
#define COUNT 3

GLFWwindow* initialize_gl_context() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        return nullptr;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return nullptr;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();
    std::cout << glGetString(GL_VERSION) << std::endl;
    return window;
}

int main(void) {
    GLFWwindow* window = initialize_gl_context();
    float positions[6]{-0.5f, -0.5f, 0.0f, 0.5f, 0.5f, -0.5f};
    unsigned int buffer_id;
    glGenBuffers(1, &buffer_id); // generate empty buffer

    glBindBuffer(GL_ARRAY_BUFFER, buffer_id); // has to be bound to use
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); // fill buffer with data

    glEnableVertexAttribArray(0); // enable the structuring that was set
    glVertexAttribPointer(
        0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // describe how the data in the buffer is structured


    std::string vertex_shader = "#version 330 core \n"
                                "\n"
                                "layout(location = 0) in vec4 position;\n"
                                "\n"
                                "void main(){\n"
                                " gl_Position = position;\n"
                                "}\n";

    std::string fragment_shader = "#version 330 core \n"
                                  "\n"
                                  "layout(location = 0) out vec4 color;\n"
                                  "\n"
                                  "void main(){\n"
                                  " color = vec4(1.0, 0.0, 0.0, 1.0);\n"
                                  "}\n";

    unsigned int shader = create_shader(vertex_shader, fragment_shader);
    glUseProgram(shader);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
