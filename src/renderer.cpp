#include "renderer.hpp"

#include "GL/glew.h"

using namespace kckn;
void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    shader.bind();
    va.bind();
    ib.bind();
    glDrawElements(GL_POINTS, ib.get_count(), GL_UNSIGNED_INT, nullptr); // draw index buffer
}

void Renderer::draw(const Object& drawable_object) const {
    drawable_object.bind();
    glDrawElements(drawable_object.get_draw_mode(), drawable_object.get_vertex_count(), GL_UNSIGNED_INT, nullptr);
}
