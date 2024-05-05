#pragma once
#include "object.hpp"
#include "vertex.hpp"
namespace kckn {
    class Point : public Object {
        Vertex vertex;
        unsigned int index;

    public:
        Point(float x, float y);

        void set_renderer_id(unsigned int id);
        void set_index_data();
        static int get_draw_mode();
        Vertex* get_vertex_data();
        unsigned int* get_index_data();
        unsigned int get_index_count();
        void set_position(float x, float y) override;

        void move(float x_offset, float y_offset) override;
        void set_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) override;
        void move_color(unsigned char r_offset, unsigned char g_offset, unsigned char b_offset, unsigned char a_offset);
    };

} // namespace kckn
