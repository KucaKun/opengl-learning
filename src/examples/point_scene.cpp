#include "examples/point_scene.hpp"

using namespace kckn;

PointScene::PointScene() : Scene() {
    renderer.create<Point>(100.f, 100.f);
}

void PointScene::on_clean() {}

void PointScene::on_render() {
    renderer.draw_all();
}

void PointScene::on_imgui() {}
