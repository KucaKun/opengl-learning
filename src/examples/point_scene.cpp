#include "examples/point_scene.hpp"

#include "global_data.hpp"
using namespace kckn;

PointScene::PointScene() : Scene() {
    auto point = renderer.create<Point>(global_data.window_width / 2, global_data.window_height / 2);
    point->set_color(0.0f, 1.0f, 0.0f, 1.0f);
    auto p2 = renderer.create<Point>(global_data.window_width / 2 + 20, global_data.window_height / 2);
    p2->set_color(0.0f, 0.0f, 1.0f, 1.0f);
}

void PointScene::on_clean() {}

void PointScene::on_render() {
    renderer.draw_all();
}

void PointScene::on_imgui() {}
