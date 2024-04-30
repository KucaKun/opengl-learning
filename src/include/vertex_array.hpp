#pragma once
#include "utils.hpp"
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"
namespace kckn {
    class VertexArray {
        unsigned int renderer_id;

    public:
        VertexArray();
        ~VertexArray();
        void add_buffer(const s_ptr<VertexBuffer>& vb, const s_ptr<VertexBufferLayout>& layout);
        void bind() const;
        void unbind() const;
    };
} // namespace kckn
