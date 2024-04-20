#include "vertex_buffer.hpp"

#include <GL/glew.h>

VertexBuffer::VertexBuffer(void* data, unsigned int size) {
    glGenBuffers(1, &renderer_id); // generate empty buffer
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id); // has to be bound to use
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // fill buffer with data
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &renderer_id);
}

void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, renderer_id);
}

void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
