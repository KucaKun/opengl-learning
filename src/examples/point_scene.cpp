#include "examples/point_scene.hpp"

#include "global_data.hpp"
using namespace kckn;

PointScene::PointScene() : Scene() {
    renderer.create<Point>(global_data.window_width / 2, global_data.window_height / 2);
}

void PointScene::on_clean() {}

void PointScene::on_render() {
    renderer.draw_all();
}

void PointScene::on_imgui() {}
