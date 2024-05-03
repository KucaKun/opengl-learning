#include "point.hpp"

#include <GL/glew.h>
namespace kckn {
    Point::Point(float x, float y) : Object(), vertex{x, y, 100, 100, 100, 255} {
        renderer_id = obj_ctr++;
        index       = renderer_id;
    }

    int Point::get_draw_mode() {
        return GL_POINTS;
    }
    Vertex* Point::get_vertex_data() {
        return &vertex;
    }
    unsigned int* Point::get_index_data() {
        return &index;
    }

    unsigned int Point::get_index_count() {
        return 1;
    }

    void Point::set_position(float x, float y) {
        vertex.position.x = x;
        vertex.position.y = y;
        has_changed       = true;
    }


    void Point::move(float x_offset, float y_offset) {
        vertex.position.x += x_offset;
        vertex.position.y += y_offset;
        has_changed = true;
    }


    void Point::set_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
        vertex.color.r = r;
        vertex.color.g = g;
        vertex.color.b = b;
        vertex.color.a = a;
        has_changed    = true;
    }


    void Point::move_color(
        unsigned char r_offset, unsigned char g_offset, unsigned char b_offset, unsigned char a_offset) {

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
} // namespace kckn
