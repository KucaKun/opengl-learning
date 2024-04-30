#include "index_buffer.hpp"

#include <GL/glew.h>

#include "global_data.hpp"

using namespace kckn;


kckn::IndexBuffer::IndexBuffer() : count(0) {
    glGenBuffers(1, &renderer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, global_data.max_index_buffer_size, nullptr, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &renderer_id);
}

void IndexBuffer::set_data(void* data, unsigned int element_offset, unsigned int element_count) {
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
