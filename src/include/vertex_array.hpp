#pragma once
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"
namespace kckn {
    class VertexArray {
        unsigned int renderer_id;

    public:
        VertexArray();
        ~VertexArray();
        void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& vbl);
        void bind() const;
        void unbind() const;
    };
} // namespace kckn
