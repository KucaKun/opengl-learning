#include "object_manager.hpp"

#include <iostream>
using namespace kckn;
ObjectManager::ObjectManager() {
    vertex_buffers.push_back(std::make_shared<VertexBuffer>());
    index_buffers.push_back(std::make_shared<IndexBuffer>());
    vertex_arrays.push_back(std::make_shared<VertexArray>());

    layouts.push_back(std::make_shared<VertexBufferLayout>());
    layouts[0]->push(GL_FLOAT, 2);
    layouts[0]->push(GL_UNSIGNED_BYTE, 4);

    vertex_arrays[0]->add_buffer(vertex_buffers[0], layouts[0]);
}


void ObjectManager::update_batch_buffers() {
    bool vertex_data_changed = false;
    auto vertex_first_offset = 0;

    bool index_data_changed = false;
    auto index_first_offset = 0;
    auto index_count        = 0;
    for (auto& object : objects) {
        if (object->has_changed) {
            auto offset = object->renderer_id * sizeof(*object->get_vertex_data());
            if (!vertex_data_changed) {
                vertex_first_offset = offset;
            }
            object->has_changed = false;
            vertex_data_changed = true;
            vertex_buffers[0]->set_data(object->get_vertex_data(), offset, sizeof(*object->get_vertex_data()));
        }

        if (object->has_mesh_changed) {
            auto offset = object->renderer_id;
            if (!index_data_changed) {
                index_first_offset = offset;
            }
            object->has_mesh_changed = false;
            index_data_changed       = true;
            index_count += object->get_index_count();
            index_buffers[0]->set_data(object->get_index_data(), offset, object->get_index_count());
        }
    }

    if (vertex_data_changed) {
        vertex_buffers[0]->bind();
        vertex_buffers[0]->upload_whole_batch_buffer();
    }

    if (index_data_changed) {
        index_buffers[0]->bind();
        index_buffers[0]->upload_whole_batch_buffer();
    }
}

void ObjectManager::bind_for_draw() {
    vertex_arrays[0]->bind();
    index_buffers[0]->bind();
}
