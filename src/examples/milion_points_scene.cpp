#include "examples/milion_points_scene.hpp"

#include <random>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/matrix.hpp"
using namespace kckn;

MilionPointsScene::MilionPointsScene() : Scene() {
    points = renderer.create_many<Point>(1000000, 500, 500);
}

void MilionPointsScene::on_clean() {}

void MilionPointsScene::on_render() {
    // do random move of every pixel
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-2, 2);
    std::uniform_int_distribution<int> disc(0.1, 0.3);

    for (auto& point : points) {
        point->move(dis(gen), dis(gen));
        point->move_color(disc(gen), disc(gen), disc(gen), 0);
    }
    renderer.draw_all();
}

void MilionPointsScene::on_imgui() {}
