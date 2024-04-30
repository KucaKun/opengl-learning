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
    class Object {
    protected:
        static size_t obj_ctr;

    public:
        size_t renderer_id;
        bool has_changed      = true;
        bool has_mesh_changed = true;

        virtual Vertex* get_vertex_data()                                                       = 0;
        virtual unsigned int* get_index_data()                                                  = 0;
        virtual unsigned int get_index_count()                                                  = 0;
        virtual void set_position(float x, float y)                                             = 0;
        virtual void move(float x_offset, float y_offset)                                       = 0;
        virtual void set_color(float r, float g, float b, float a)                              = 0;
        virtual void move_color(float r_offset, float g_offset, float b_offset, float a_offset) = 0;
    };

    class Point : public Object {
        Vertex vertex;
        unsigned int index;

    public:
        Point(float x, float y) : Object(), vertex{x, y, 0.2f, 0.3f, 0.6f, 1.0f} {
            renderer_id = obj_ctr++;
            index       = renderer_id;
        }

        static int get_draw_mode() {
            return GL_POINTS;
        }

        Vertex* get_vertex_data() {
            return &vertex;
        }
        unsigned int* get_index_data() {
            return &index;
        }
        unsigned int get_index_count() {
            return 1;
        }
        void set_position(float x, float y) override {
            vertex.position.x = x;
            vertex.position.y = y;
            has_changed       = true;
        }

        void move(float x_offset, float y_offset) override {
            vertex.position.x += x_offset;
            vertex.position.y += y_offset;
            has_changed = true;
        }

        void set_color(float r, float g, float b, float a) override {
            vertex.color.r = r;
            vertex.color.g = g;
            vertex.color.b = b;
            vertex.color.a = a;
            has_changed    = true;
        }
        void move_color(float r_offset, float g_offset, float b_offset, float a_offset) {

            vertex.color.r += r_offset;
            vertex.color.g += g_offset;
            vertex.color.b += b_offset;
            if (vertex.color.r > 1) {
                vertex.color.r -= 1;
            }
            if (vertex.color.g > 1) {
                vertex.color.g -= 1;
            }
            if (vertex.color.b > 1) {
                vertex.color.b -= 1;
            }
            has_changed = true;
        }
    };

} // namespace kckn
