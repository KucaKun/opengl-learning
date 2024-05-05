#include "object_manager.hpp"

#include <iostream>
using namespace kckn;

ObjectManager::ObjectManager() {
    vertex_buffer = std::make_shared<VertexBuffer>();
    index_buffer  = std::make_shared<IndexBuffer>();
    vertex_array  = std::make_shared<VertexArray>();
    layout        = std::make_shared<VertexBufferLayout>();

    layout->push(GL_FLOAT, 2);
    layout->push(GL_UNSIGNED_BYTE, 4);

    vertex_array->add_buffer(vertex_buffer, layout);
}


void ObjectManager::update_batch_buffers() {
    bool vertex_data_changed = false;
    auto vertex_first_offset = 0;

    bool index_data_changed = false;
    auto index_first_offset = 0;
    auto index_count        = 0;
    for (auto& object : drawable_objects) {
        if (object->has_changed) {
            auto offset = object->renderer_id * sizeof(*object->get_vertex_data());
            if (!vertex_data_changed) {
                vertex_first_offset = offset;
            }
            object->has_changed = false;
            vertex_data_changed = true;
            vertex_buffer->set_data(object->get_vertex_data(), offset, sizeof(*object->get_vertex_data()));
        }

        if (object->has_mesh_changed) {
            auto offset = object->renderer_id;
            if (!index_data_changed) {
                index_first_offset = offset;
            }
            object->has_mesh_changed = false;
            index_data_changed       = true;
            index_count += object->get_index_count();
            index_buffer->set_data(object->get_index_data(), offset, object->get_index_count());
        }
    }

    if (vertex_data_changed) {
        vertex_buffer->bind();
        vertex_buffer->upload_whole_batch_buffer();
    }

    if (index_data_changed) {
        index_buffer->bind();
        index_buffer->upload_whole_batch_buffer();
    }
}

void ObjectManager::bind_for_draw() {
    vertex_array->bind();
    index_buffer->bind();
}
