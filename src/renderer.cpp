#include "renderer.hpp"

#include "GL/glew.h"


void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    shader.bind();
    va.bind();
    ib.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // draw index buffer
}
