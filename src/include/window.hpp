#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <memory>

namespace kckn {
    class Window {
        GLFWwindow* window;
        int width, height;
        int frame_ctr;
        bool show_debug_window;
        const char* glsl_version;

    public:
        Window(int width, int height, bool hidden = false);
        ~Window();
        bool should_close();
        void clear();
        void draw_imgui();
        void prepare_frame();
        void prepare_imgui();
        void finalize_frame();
        void unbind();
    };
} // namespace kckn
