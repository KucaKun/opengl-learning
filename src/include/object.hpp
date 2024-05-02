#pragma once
#include "vertex.hpp"
namespace kckn {
    class Object {
    protected:
        static unsigned int obj_ctr;

    public:
        unsigned int renderer_id;
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
} // namespace kckn
