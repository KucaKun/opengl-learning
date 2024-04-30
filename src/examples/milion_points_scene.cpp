#include "examples/milion_points_scene.hpp"

#include <random>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/matrix.hpp"
using namespace kckn;

MilionPointsScene::MilionPointsScene() : Scene() {
    // auto ctr = 0;
    // for (int x = 0; x < 1920; x++) {
    //     for (int y = 0; y < 1080; y++) {
    //         points.push_back(Point(x, y));
    //         ctr++;
    //         if (ctr == 1000000) {
    //             return;
    //         }
    //     }
    // }
}

void MilionPointsScene::on_clean() {}

void MilionPointsScene::on_render() {
    // glm::mat4 mvp = glm::ortho(-1.0f, 1920.0f, -1.0f, 1080.0f, -1.0f, 1.0f);
    // points[0].set_mvp(mvp);

    // std::random_device rd;
    // std::mt19937 gen(rd());
    // std::uniform_int_distribution<> dis(0, points.size() - 1);

    // for (size_t i = 0; i < 100000; i++) {
    //     int random_point = dis(gen);
    //     points[random_point].move(1.0f, 0.0f);
    // }


    // renderer.draw(points);
}

void MilionPointsScene::on_imgui() {}
