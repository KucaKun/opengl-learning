#include "vertex_buffer.hpp"

#include <GL/glew.h>

#include "global_data.hpp"

using namespace kckn;

VertexBuffer::VertexBuffer() {
    glGenBuffers(1, &renderer_id); // generate empty buffer
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
    glBufferData(GL_ARRAY_BUFFER, global_data.max_vertex_buffer_size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &renderer_id);
}

void VertexBuffer::set_data(void* data, unsigned int offset, unsigned int size) {
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

int VertexBuffer::get_batch_offset(int obj_id) const {
    return obj_id * sizeof(Vertex);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
