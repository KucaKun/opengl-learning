#include "examples/point_scene.hpp"

using namespace kckn;

PointScene::PointScene(std::shared_ptr<Window> _window) : Scene(_window), point(100, 100) {}

void PointScene::on_clean() {}

void PointScene::on_render() {
    point.move(0.1, 0.1);
    renderer.draw(point);
}

void PointScene::on_imgui() {}
