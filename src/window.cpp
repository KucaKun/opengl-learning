#include "window.hpp"

#include <iostream>

#include "error_handling.hpp"
#include "examples/examples.hpp"
using namespace kckn;

Window::Window(int _width, int _height) : width(_width), height(_height), frame_ctr(0), show_debug_window(true) {

    /* Initialize the library */
    if (!glfwInit()) {
        std::terminate();
    }
    glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::terminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();

    glfwSwapInterval(1);
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(error, nullptr);
    std::cout << glGetString(GL_VERSION) << std::endl;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

Window::~Window() {
    unbind();
}


bool Window::should_close() {
    return glfwWindowShouldClose(window);
}

void Window::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::prepare_frame(std::shared_ptr<Scene>& scene) {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    ImGui::Begin("Hello, world!");
    ImGui::Text("counter = %d", frame_ctr);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();

    if (scene) {
        ImGui::Begin("Scene chooser");
        if (ImGui::Button("End scene")) {
            scene.reset();
        }
        ImGui::End();
    } else {
        ImGui::Begin("Scene chooser");
        if (ImGui::Button("Point Scene")) {
            scene = std::make_shared<PointScene>();
        }
        if (ImGui::Button("Blank Scene")) {
            scene = std::make_shared<Scene>();
        }
        if (ImGui::Button("Milion Points Scene")) {
            scene = std::make_shared<MilionPointsScene>();
        }
        ImGui::End();
    }

    ImGui::Render();
    glViewport(0, 0, width, height);
}

void Window::draw_imgui() {
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::finalize_frame() {
    glfwSwapBuffers(window);
    frame_ctr++;
}

void Window::unbind() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}
