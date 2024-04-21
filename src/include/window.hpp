#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
namespace kckn {
    class Window {
        GLFWwindow* window;
        int width, height;
        unsigned long long frame_ctr;
        bool show_debug_window;

    public:
        Window(int width, int height);
        bool should_close();
        void draw_imgui();
        void prepare_frame();
        void finalize_frame();
        void unbind();
    };
} // namespace kckn
