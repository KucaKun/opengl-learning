#pragma once
#include "object.hpp"
#include "scene.hpp"
namespace kckn {
    class MilionPointsScene : public Scene {
    private:
        std::vector<Point> points;

    public:
        MilionPointsScene();
        void on_clean() override;
        void on_render() override;
        void on_imgui() override;
    };
} // namespace kckn