#include "index_buffer.hpp"

#include <GL/glew.h>
#include <cstring>

#include "global_data.hpp"

using namespace kckn;


kckn::IndexBuffer::IndexBuffer() : count(0), batch_buffer(new unsigned int[global_data.max_index_buffer_size]) {
    glGenBuffers(1, &renderer_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, global_data.max_index_buffer_size, nullptr, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &renderer_id);
}

void IndexBuffer::set_data(unsigned int* data, unsigned int element_offset, unsigned int element_count) {
    std::memcpy(batch_buffer.get() + element_offset, data, element_count * sizeof(unsigned int));
    count += element_count;
}

void IndexBuffer::upload_whole_batch_buffer() {
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, global_data.max_index_buffer_size, batch_buffer.get());
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
