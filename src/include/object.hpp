#pragma once
#include <memory>
#include <utility>
#include <vector>

#include "index_buffer.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"
namespace kckn {
    struct Vertex {
        float x, y;
    };

    class Object {
    public:
        std::unique_ptr<VertexArray> va;
        std::unique_ptr<VertexBuffer> vb;
        std::unique_ptr<VertexBufferLayout> layout;
        std::unique_ptr<IndexBuffer> ib;
        std::unique_ptr<Shader> shader;
        int draw_mode;

    public:
        int get_draw_mode() const {
            return draw_mode;
        }
        int get_vertex_count() const {
            return ib->get_count();
        }
        void set_mvp(glm::mat4& mvp) {
            shader->bind();
            shader->set_uniform<glm::mat4>("u_mvp", &mvp[0][0]);
        }
        void set_color(float r, float g, float b, float a) {
            shader->set_uniform<float>("u_color", r, g, b, a);
        }
        void set_position(int x, int y) {
            shader->set_uniform<int>("u_position", x, y);
        }
        void bind() const {
            shader->bind();
            va->bind();
            ib->bind();
        }
    };

    class Point : public Object {
        Vertex vertex;
        unsigned int index;

    public:
        Point(float x, float y) : vertex(x, y), index(0) {
            va     = std::make_unique<VertexArray>();
            vb     = std::make_unique<VertexBuffer>(&vertex, sizeof(Vertex));
            ib     = std::make_unique<IndexBuffer>(&index, 1);
            layout = std::make_unique<VertexBufferLayout>();
            layout->push(GL_FLOAT, 2);
            va->add_buffer(*vb, *layout);
            shader    = std::make_unique<Shader>("color.glsl");
            draw_mode = GL_POINTS;
            bind();
        }
    };
    class Triangle : public Object {
        Vertex verticies[3];
        unsigned int indicies[3];

    public:
        Triangle(float x, float y, float a, float h)
            : verticies(Vertex{x - a, y}, Vertex{x + a, y}, Vertex{x, y + h}),
              indicies(0, 1, 2) {
            va     = std::make_unique<VertexArray>();
            vb     = std::make_unique<VertexBuffer>(&verticies, 3 * sizeof(Vertex));
            ib     = std::make_unique<IndexBuffer>(indicies, 3);
            layout = std::make_unique<VertexBufferLayout>();
            layout->push(GL_FLOAT, 2);
            va->add_buffer(*vb, *layout);
            shader    = std::make_unique<Shader>("color.glsl");
            draw_mode = GL_TRIANGLES;
            bind();
        }
    };
} // namespace kckn
