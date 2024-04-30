#include "examples/raw_scene.hpp"

#include <glm/gtc/matrix_transform.hpp>
using namespace kckn;

RawScene::RawScene() : Scene(), shader("basic.glsl") {
    float positions[] = {
        // 0
        -0.5f,
        -0.5f,
        // 1
        0.5f,
        -0.5f,
        // 2
        0.5f,
        0.5f,
        // 3
        -0.5f,
        0.5f,
    };
    unsigned int indices[]{0, 1, 2, 2, 3, 0};

    // Prepare buffer
    unsigned int buffer_id;
    glGenBuffers(1, &buffer_id); // generate empty buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id); // has to be bound to use
    glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW); // fill buffer with data

    // vertex array
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Prepare attributes
    // Need to be made after vertex array is bound
    glVertexAttribPointer(
        0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // describe how the data in the buffer is structured
    glEnableVertexAttribArray(0); // enable the structuring that was set

    // Prepare index buffer
    unsigned int ibo; // index buffer object
    glGenBuffers(1, &ibo); // generate empty buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // has to be bound to use
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW); // fill buffer with data

    // load shaders
    shader.bind();
}

void RawScene::on_clean() {}

void RawScene::on_render() {
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // draw index buffer
}

void RawScene::on_imgui() {}
