#include "examples/milion_points_scene.hpp"

#include <random>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/matrix.hpp"
using namespace kckn;

MilionPointsScene::MilionPointsScene() : Scene() {
    particles =
        renderer.create_many<RandomParticle>(1000000, global_data.window_width / 2, global_data.window_height / 2);
}

void MilionPointsScene::on_clean() {}

void MilionPointsScene::on_render() {

    for (auto& particle : particles) {
        particle->move_randomly();
    }
    renderer.draw_all();
}

void MilionPointsScene::on_imgui() {}
