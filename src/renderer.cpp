#include "renderer.hpp"

#include "GL/glew.h"

using namespace kckn;
Renderer::Renderer() {
    // Add default shaders
    shader_register["color.glsl"].push_back(std::make_shared<Shader>("color.glsl"));
    shader_register["color.glsl"][0]->set_default_uniforms();
    shader_register["texture.glsl"].push_back(std::make_shared<Shader>("texture.glsl"));
    shader_register["texture.glsl"][0]->set_default_uniforms();

    vb_register.push_back(std::make_shared<VertexBuffer>());
    ib_register.push_back(std::make_shared<IndexBuffer>());
    va_register.push_back(std::make_shared<VertexArray>());

    layout_register.push_back(std::make_shared<VertexBufferLayout>());
    layout_register[0]->push(GL_FLOAT, 2);
    layout_register[0]->push(GL_FLOAT, 4);

    va_register[0]->add_buffer(vb_register[0], layout_register[0]);
}

void Renderer::draw_all() {
    bool vertex_data_changed = false;
    auto vertex_first_offset = 0;

    bool index_data_changed = false;
    auto index_first_offset = 0;
    auto index_count        = 0;
    for (auto& object : object_register.at(GL_POINTS)) {

        if (object->has_changed) {
            auto offset = object->renderer_id * sizeof(object->get_vertex_data());
            if (!vertex_data_changed) {
                vertex_first_offset = offset;
            }
            object->has_changed = false;
            vertex_data_changed = true;
            vb_register[0]->set_data(object->get_vertex_data(), offset, sizeof(*object->get_vertex_data()));
        }

        if (object->has_mesh_changed) {
            auto offset = object->renderer_id;
            if (!index_data_changed) {
                index_first_offset = offset;
            }
            object->has_mesh_changed = false;
            index_data_changed       = true;
            index_count += object->get_index_count();
            ib_register[0]->set_data(object->get_index_data(), offset, object->get_index_count());
        }
    }

    vb_register[0]->bind();
    if (vertex_data_changed) {
        vb_register[0]->upload_whole_batch_buffer();
    }

    ib_register[0]->bind();
    if (index_data_changed) {
        ib_register[0]->upload_whole_batch_buffer();
    }
    va_register[0]->bind();
    shader_register.at("color.glsl")[0]->bind();
    glDrawElements(GL_POINTS, global_data.max_index_buffer_size / sizeof(unsigned int), GL_UNSIGNED_INT, nullptr);
}
