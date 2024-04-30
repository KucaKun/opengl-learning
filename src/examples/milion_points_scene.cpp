#include "examples/milion_points_scene.hpp"

#include <random>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/matrix.hpp"
using namespace kckn;

MilionPointsScene::MilionPointsScene() : Scene() {
    renderer.create_many<Point>(1000000, 500, 500);
}

void MilionPointsScene::on_clean() {}

void MilionPointsScene::on_render() {
    renderer.draw_all();
}

void MilionPointsScene::on_imgui() {}
