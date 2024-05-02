#include "renderer.hpp"

#include "GL/glew.h"

using namespace kckn;
Renderer::Renderer() {
    // Add default shaders
    shader_register["color.glsl"].push_back(std::make_shared<Shader>("color.glsl"));
    shader_register["color.glsl"][0]->set_default_uniforms();
    shader_register["texture.glsl"].push_back(std::make_shared<Shader>("texture.glsl"));
    shader_register["texture.glsl"][0]->set_default_uniforms();
}

void Renderer::draw_all() {
    shader_register.at("color.glsl")[0]->bind();
    object_manager.update_batch_buffers();
    object_manager.bind_for_draw();
    glDrawElements(GL_POINTS, global_data.max_index_buffer_size / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
}
