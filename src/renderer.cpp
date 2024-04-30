#include "renderer.hpp"

#include "GL/glew.h"

using namespace kckn;
Renderer::Renderer() {
    // Add default shaders

    shader_register["color.glsl"].push_back(std::make_shared<Shader>("color.glsl"));
    shader_register["texture.glsl"].push_back(std::make_shared<Shader>("texture.glsl"));


    vb_register.push_back(std::make_shared<VertexBuffer>());
    ib_register.push_back(std::make_shared<IndexBuffer>());
    va_register.push_back(std::make_shared<VertexArray>());

    layout_register.push_back(std::make_shared<VertexBufferLayout>());
    layout_register[0]->push(GL_FLOAT, 2);
    layout_register[0]->push(GL_FLOAT, 4);

    va_register[0]->add_buffer(vb_register[0], layout_register[0]);
}

void Renderer::draw_all() {
    for (auto& object : object_register.at(GL_POINTS)) {
        if (object->has_changed) {
            object->has_changed = false;

            auto offset = object->renderer_id * sizeof(object);
            vb_register[0]->bind();
            vb_register[0]->set_data(object->get_vertex_data(), offset, 6 * sizeof(float));
            ib_register[0]->bind();
            ib_register[0]->set_data(object->get_index_data(), offset, object->get_index_count());
        }
    }
    va_register[0]->bind();
    shader_register.at("color.glsl")[0]->bind();
    glDrawElements(GL_POINTS, ib_register[0]->get_count(), GL_UNSIGNED_INT, nullptr);
}
