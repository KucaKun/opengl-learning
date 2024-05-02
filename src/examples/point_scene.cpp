#include "examples/point_scene.hpp"

#include "global_data.hpp"
#include "point.hpp"
using namespace kckn;

PointScene::PointScene() : Scene() {
    auto point = renderer.object_manager.create<Point>(global_data.window_width / 2, global_data.window_height / 2);
    point->set_color(0, 255, 0, 255);
    auto p2 = renderer.object_manager.create<Point>(global_data.window_width / 2 + 20, global_data.window_height / 2);
    p2->set_color(0, 0, 255, 255);
}

void PointScene::on_clean() {}

void PointScene::on_render() {
    renderer.draw_all();
}

void PointScene::on_imgui() {}
