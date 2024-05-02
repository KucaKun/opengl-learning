#include "vertex_buffer.hpp"

#include <GL/glew.h>
#include <cstring>

#include "global_data.hpp"
using namespace kckn;

VertexBuffer::VertexBuffer() : batch_buffer(new unsigned char[global_data.max_vertex_buffer_size]) {
    glGenBuffers(1, &renderer_id); // generate empty buffer
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
    glBufferData(GL_ARRAY_BUFFER, global_data.max_vertex_buffer_size, nullptr, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &renderer_id);
}

void VertexBuffer::set_data(void* data, unsigned int offset, unsigned int size) {
    std::memcpy(batch_buffer.get() + offset, data, size);
}

void VertexBuffer::upload_whole_batch_buffer() {
    glBufferSubData(GL_ARRAY_BUFFER, 0, global_data.max_vertex_buffer_size, batch_buffer.get());
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
