#pragma once
#include "index_buffer.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"
namespace kckn {
    class RawScene : public Scene {
        Shader shader;

    public:
        RawScene();
        void on_clean() override;
        void on_render() override;
        void on_imgui() override;
    };
} // namespace kckn
