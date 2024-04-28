#pragma once
#include "index_buffer.hpp"
#include "object.hpp"
#include "shader.hpp"
#include "vertex_array.hpp"
namespace kckn {

    class Renderer {
    private:
    public:
        void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
        void draw(const Object& drawable_object) const;
        template <typename T>
        void draw(const std::vector<T>& drawable_objects) const {
            // it actually binds all the objects of the same type because of my singleton batch implementation
            drawable_objects[0].bind();
            glDrawElements(
                drawable_objects[0].get_draw_mode(), drawable_objects[0].get_vertex_count(), GL_UNSIGNED_INT, nullptr);
        }
    };
} // namespace kckn
