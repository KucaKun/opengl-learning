#pragma once
#include "object.hpp"
#include "vertex.hpp"
namespace kckn {
    class Point : public Object {
        Vertex vertex;
        unsigned int index;

    public:
        Point(float x, float y);

        static int get_draw_mode();
        Vertex* get_vertex_data();
        unsigned int* get_index_data();
        unsigned int get_index_count();
        void set_position(float x, float y) override;

        void move(float x_offset, float y_offset) override;
        void set_color(float r, float g, float b, float a) override;
        void move_color(float r_offset, float g_offset, float b_offset, float a_offset);
    };

} // namespace kckn
