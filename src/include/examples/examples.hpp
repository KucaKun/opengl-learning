#pragma once
/// This is a convinience header file that includes all the examples
#include "milion_points_scene.hpp"
#include "point_scene.hpp"
#include "raw_scene.hpp"
#include "utils.hpp"
namespace kckn {
    static auto scene_chooser(s_ptr<Scene> scene) {
        if (scene) {
            ImGui::Begin("Scene chooser");
            if (ImGui::Button("End scene")) {
                scene.reset();
            }
            ImGui::End();
        } else {
            ImGui::Begin("Scene chooser");
            if (ImGui::Button("Point Scene")) {
                scene = std::make_shared<PointScene>();
            }
            if (ImGui::Button("Blank Scene")) {
                scene = std::make_shared<Scene>();
            }
            if (ImGui::Button("Milion Points Scene")) {
                scene = std::make_shared<MilionPointsScene>();
            }
            ImGui::End();
        }
        return scene;
    }
} // namespace kckn
