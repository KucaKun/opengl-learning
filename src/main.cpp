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

    Triangle triangle(500, 300, 100, 100);
    Triangle triangle2(300, 500, 80, 80);
    Point aaa(200, 200);

    glm::mat4 proj = glm::ortho(0.f, 1080.f, 0.f, 720.f, -1.f, 1.f);

    aaa.set_mvp(proj);
    aaa.set_color(100, 200, 255, 255);

    triangle.set_mvp(proj);
    triangle.set_color(0, 1, 222, 234);

    triangle2.set_mvp(proj);
    triangle2.set_color(100, 1, 0, 234);

    while (!window.should_close()) {
        window.prepare_frame();
        renderer.clear();
        renderer.draw(triangle);
        renderer.draw(triangle2);
        renderer.draw(aaa);
        window.draw_imgui();
        window.finalize_frame();
    }
    window.unbind();
    return 0;
}
