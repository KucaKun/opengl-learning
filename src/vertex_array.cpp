#include "vertex_array.hpp"


VertexArray::VertexArray() {
    glGenVertexArrays(1, &renderer_id);
    glBindVertexArray(renderer_id);
}

VertexArray::~VertexArray() {}

void VertexArray::add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
    auto i      = 0;
    auto offset = 0;
    for (auto& element : layout.get_elements()) {
        // describe how the data in the buffer is structured
        glVertexAttribPointer(
            i, element.count, element.type, element.normalized, layout.get_stride(), (const void*) offset);

        // enable the structuring that was set
        glEnableVertexAttribArray(i);
        offset += element.get_size();
        i++;
    }
}

void VertexArray::bind() const {
    glBindVertexArray(renderer_id);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}
