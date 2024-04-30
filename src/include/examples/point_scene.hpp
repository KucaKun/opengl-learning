#pragma once
#include "object.hpp"
#include "scene.hpp"
namespace kckn {
    class PointScene : public Scene {
    public:
        PointScene();
        void on_clean() override;
        void on_render() override;
        void on_imgui() override;
    };
} // namespace kckn
