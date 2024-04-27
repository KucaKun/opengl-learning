#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gtest/gtest.h>
namespace kckn {
    class GLContextFixture : public ::testing::Test {
        GLFWwindow* offscreen_context;

    public:
        virtual void SetUp() {
            // gl context without window
            if (!glfwInit()) {
                std::terminate();
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
            offscreen_context = glfwCreateWindow(640, 480, "", NULL, NULL);

            glfwMakeContextCurrent(offscreen_context);
            glewInit();
        }
        void TearDown() {
            glfwDestroyWindow(offscreen_context);
            glfwTerminate();
        }
    };
} // namespace kckn
