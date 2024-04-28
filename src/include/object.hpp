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
    struct Position {
        float x, y;
    };
    struct Color {
        float r, g, b, a;
    };
    class Object {
    protected:
        unsigned int renderer_id;
        int draw_mode;
        Position position;
        Color color;

    public:
        int get_draw_mode() const {
            return draw_mode;
        }
        virtual void set_position(float x, float y)                                             = 0;
        virtual void move(float x_offset, float y_offset)                                       = 0;
        virtual void set_color(float r, float g, float b, float a)                              = 0;
        virtual void move_color(float r_offset, float g_offset, float b_offset, float a_offset) = 0;
        virtual int get_vertex_count() const                                                    = 0;
        virtual void set_mvp(glm::mat4& mvp)                                                    = 0;
        virtual void bind() const                                                               = 0;
    };

    class Point : public Object {
        static unsigned int obj_ctr;
        static std::unique_ptr<VertexBuffer> vb;
        static std::unique_ptr<IndexBuffer> ib;
        static std::unique_ptr<VertexBufferLayout> layout;
        static std::unique_ptr<Shader> shader;
        static std::unique_ptr<VertexArray> va;
        Vertex vertex;
        unsigned int vertex_index;

    public:
        Point(float x, float y) : Object() {
            // singleton initialization
            if (!vb) {
                vb     = std::make_unique<VertexBuffer>();
                ib     = std::make_unique<IndexBuffer>();
                shader = std::make_unique<Shader>("color.glsl");
                layout = std::make_unique<VertexBufferLayout>();
                va     = std::make_unique<VertexArray>();
                layout->push(GL_FLOAT, 2);
                layout->push(GL_FLOAT, 4);
                va->add_buffer(*vb, *layout);
            }

            renderer_id  = obj_ctr;
            vertex_index = 0 + renderer_id;
            obj_ctr += 1;

            draw_mode = GL_POINTS;

            ib->set_data(&vertex_index, renderer_id, 1);
            set_position(x, y);
            set_color(0.2, 0.3, 0.6, 1.0);
        }

        int get_vertex_count() const override {
            return ib->get_count();
        }

        void set_position(float x, float y) override {
            position.x       = x;
            position.y       = y;
            int batch_offset = vb->get_batch_offset(renderer_id);
            vb->set_data(&position, batch_offset + offsetof(Vertex, x), 2 * sizeof(float));
        }

        void move(float x_offset, float y_offset) override {
            position.x += x_offset;
            position.y += y_offset;
            int batch_offset = vb->get_batch_offset(renderer_id);
            vb->set_data(&position, batch_offset + offsetof(Vertex, x), 2 * sizeof(float));
        }

        void set_color(float r, float g, float b, float a) override {
            color.r          = r;
            color.g          = g;
            color.b          = b;
            color.a          = a;
            int batch_offset = vb->get_batch_offset(renderer_id);
            vb->set_data(&color, batch_offset + offsetof(Vertex, r), 4 * sizeof(float));
        }
        void move_color(float r_offset, float g_offset, float b_offset, float a_offset) {

            color.r += r_offset;
            color.g += g_offset;
            color.b += b_offset;
            if (color.r > 1) {
                color.r -= 1;
            }
            if (color.g > 1) {
                color.g -= 1;
            }
            if (color.b > 1) {
                color.b -= 1;
            }
            int batch_offset = vb->get_batch_offset(renderer_id);
            vb->set_data(&color, batch_offset + offsetof(Vertex, r), 3 * sizeof(float));
        }

        void set_mvp(glm::mat4& mvp) override {
            shader->bind();
            shader->set_uniform<glm::mat4>("u_mvp", &mvp[0][0]);
        }

        void bind() const override {
            shader->bind();
            va->bind();
            ib->bind();
        }
    };

} // namespace kckn
