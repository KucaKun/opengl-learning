#include "index_buffer.hpp"

#include <GL/glew.h>

IndexBuffer::IndexBuffer(void* data, unsigned int count) : count(count) {
    glGenBuffers(1, &renderer_id); // generate empty buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id); // has to be bound to use
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); // fill buffer with data
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &renderer_id);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
