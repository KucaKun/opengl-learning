#include <gtest/gtest.h>

#include "shader.hpp"
#include "tests/gl_context_fixture.hpp"
using namespace kckn;

TEST_F(GLContextFixture, CompileShader) {
    ShaderSources sources;
    sources.vertex_shader   = R"(
        #version 330 core
        layout(location = 0) in vec4 position;
        void main() {
            gl_Position = position;
        }
    )";
    sources.fragment_shader = R"(
        #version 330 core
        layout(location = 0) out vec4 color;
        void main() {
            color = vec4(1.0, 0.0, 0.0, 1.0);
        }
    )";


    Shader shader(sources); // this should not throw
    shader.bind();
    shader.unbind();
}

// This test checks is the same as before, but checks if fixture works properly on multiple tests
TEST_F(GLContextFixture, CompileShader2) {
    ShaderSources sources;
    sources.vertex_shader   = R"(
        #version 330 core
        layout(location = 0) in vec4 position;
        void main() {
            gl_Position = position;
        }
    )";
    sources.fragment_shader = R"(
        #version 330 core
        layout(location = 0) out vec4 color;
        void main() {
            color = vec4(1.0, 0.0, 0.0, 1.0);
        }
    )";


    Shader shader(sources); // this should not throw
    shader.bind();
    shader.unbind();
}

TEST_F(GLContextFixture, CompileShaderWithUniform) {
    ShaderSources sources;
    sources.vertex_shader   = R"(
        #version 330 core
        layout(location = 0) in vec4 position;
        uniform mat4 u_mvp;
        void main() {
            gl_Position = u_mvp * position;
        }
    )";
    sources.fragment_shader = R"(
        #version 330 core
        layout(location = 0) out vec4 color;
        void main() {
            color = vec4(1.0, 0.0, 0.0, 1.0);
        }
    )";

    Shader shader(sources);
    shader.bind();
    // this should not throw
    glm::mat4 mvp = glm::mat4(1.0f);
    shader.set_uniform<glm::mat4>("u_mvp", &mvp[0][0]);
    shader.unbind();
}
