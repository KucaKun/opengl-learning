#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "object.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "window.hpp"
using namespace kckn;


int main(void) {
    Window window(1080, 720);
    Renderer renderer;
    float center = 320.f;
    float size   = 100.f;
    // float verticies[][4] = {
    //     {center - size, center - size, 0.0f, 0.0f},
    //     {center + size, center - size, 1.0f, 0.0f},
    //     {center + size, center + size, 1.0f, 1.0f},
    //     {center - size, center + size, 0.0f, 1.0f},
    // };
    // int layout[][2] = {
    //     {GL_FLOAT, 2},
    //     {GL_FLOAT, 2},
    // };

    // unsigned int indices[]{0, 1, 2, 2, 3, 0};


    Object object(
        {
            {center - size, center - size, 0.0f, 0.0f},
            {center + size, center - size, 1.0f, 0.0f},
            {center + size, center + size, 1.0f, 1.0f},
            {center - size, center + size, 0.0f, 1.0f},
        },
        {
            {GL_FLOAT, 2},
            {GL_FLOAT, 2},
        },
        {0, 1, 2, 2, 3, 0},
        "basic.glsl",
        GL_TRIANGLES);

    glm::mat4 proj  = glm::ortho(0.f, 640.f, 0.f, 480.f, -1.f, 1.f);
    glm::mat4 view  = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 mvp   = proj * view * model;

    object.set_mvp(mvp);
    object.set_texture("witek.png", 0);

    while (!window.should_close()) {
        window.prepare_frame();
        renderer.clear();
        renderer.draw(object.va, object.ib, object.shader);
        // window.draw_imgui();
        window.finalize_frame();
    }
    window.unbind();
    return 0;
}
