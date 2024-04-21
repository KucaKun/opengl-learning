#pragma once
#include "index_buffer.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"
namespace kckn {

    class Renderer {
    private:
    public:
        void clear();
        void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    };
} // namespace kckn
