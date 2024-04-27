#include "examples/point_scene.hpp"

using namespace kckn;

PointScene::PointScene() : Scene(), point(100, 100) {}

void PointScene::on_clean() {}

void PointScene::on_render() {
    point.move(0.1, 0.1);
    renderer.draw(point);
}

void PointScene::on_imgui() {}
