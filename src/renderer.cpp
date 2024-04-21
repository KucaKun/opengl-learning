#include "renderer.hpp"

#include "GL/glew.h"

using namespace kckn;
void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    shader.bind();
    va.bind();
    ib.bind();
    glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, nullptr); // draw index buffer
}
