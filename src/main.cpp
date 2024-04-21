#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "index_buffer.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"
#include "window.hpp"
using namespace kckn;


int main(void) {
    Window window(1080, 720);
    Renderer renderer;
    float center         = 320.f;
    float size           = 100.f;
    float verticies[][4] = {
        {center - size, center - size, 0.0f, 0.0f},
        {center + size, center - size, 1.0f, 0.0f},
        {center + size, center + size, 1.0f, 1.0f},
        {center - size, center + size, 0.0f, 1.0f},
    };
    unsigned int indices[]{0, 1, 2, 2, 3, 0};
    VertexArray va;
    int floats_per_vertex = 4;
    int verticies_count   = 4;
    VertexBuffer vb(verticies, verticies_count * floats_per_vertex * sizeof(float));

    VertexBufferLayout layout;
    layout.push(GL_FLOAT, 2);
    layout.push(GL_FLOAT, 2);

    va.add_buffer(vb, layout);

    IndexBuffer ib(indices, 6);
    Shader shader("basic.glsl");
    shader.bind();

    glm::mat4 proj  = glm::ortho(0.f, 640.f, 0.f, 480.f, -1.f, 1.f);
    glm::mat4 view  = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 200, 0));
    glm::mat4 mvp   = proj * view * model;

    shader.set_uniform<glm::mat4>("u_mvp", &mvp[0][0]);
    Texture texture("witek.png");
    texture.bind(0);
    shader.set_uniform<int>("u_texture", 0);
    while (!window.should_close()) {
        window.prepare_frame();
        renderer.clear();
        renderer.draw(va, ib, shader);
        window.draw_imgui();
        window.finalize_frame();
    }
    shader.unbind();
    window.unbind();
    return 0;
}
