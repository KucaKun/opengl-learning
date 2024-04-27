#include "index_buffer.hpp"

#include <GL/glew.h>

using namespace kckn;


kckn::IndexBuffer::IndexBuffer() : count(0) {
    glGenBuffers(1, &renderer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0xffff, nullptr, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &renderer_id);
}

void IndexBuffer::set_data(void* data, unsigned int element_offset, unsigned int element_count) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
    glBufferSubData(
        GL_ELEMENT_ARRAY_BUFFER, element_offset * sizeof(unsigned int), element_count * sizeof(unsigned int), data);
    count += element_count;
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
