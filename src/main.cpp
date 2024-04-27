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
int amain(void) {
    Window window(1080, 720);
    Renderer renderer;

    glm::mat4 proj          = glm::ortho(0.f, 1080.f, 0.f, 720.f, -1.f, 1.f);
    unsigned int indicies[] = {0};
    float verticies[]       = {100, 100, 0, 200, 255, 255};

    VertexBuffer vb;
    vb.set_data(verticies, 0, sizeof(verticies));
    VertexBufferLayout vbl;
    vbl.push(GL_FLOAT, 2);
    vbl.push(GL_FLOAT, 4);
    IndexBuffer ib;
    ib.set_data(indicies, 0, 1);
    VertexArray va;
    va.add_buffer(vb, vbl);

    Shader shader("color.glsl");
    shader.bind();
    shader.set_uniform<glm::mat4>("u_mvp", &proj[0][0]);

    while (!window.should_close()) {
        window.prepare_frame();
        renderer.clear();
        renderer.draw(va, ib, shader);
        window.draw_imgui();
        window.finalize_frame();
    }
    window.unbind();
    return 0;
}

int main(void) {
    Window window(1080, 720);
    Renderer renderer;

    glm::mat4 proj = glm::ortho(0.f, 1080.f, 0.f, 720.f, -1.f, 1.f);

    Point p(100, 200);
    p.set_mvp(proj);

    while (!window.should_close()) {
        window.prepare_frame();
        renderer.clear();

        p.move(0.01, 0.01);
        renderer.draw(p);
        window.draw_imgui();
        window.finalize_frame();
    }
    window.unbind();
    return 0;
}
