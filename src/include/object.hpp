#pragma once
#include <list>

#include "vertex.hpp"
namespace kckn {
    class Object {
    protected:
    public:
        /// Manged by object_manager, renderer_id is used to get data offset in batch buffers
        /// 0xffffffff is an invalid id, object is nondrawable
        unsigned int renderer_id = 0xffffffff;

        bool has_changed      = true;
        bool has_mesh_changed = true;


        virtual void set_renderer_id(unsigned int id) = 0;
        virtual void set_index_data()                 = 0;

        virtual Vertex* get_vertex_data()                                                          = 0;
        virtual unsigned int* get_index_data()                                                     = 0;
        virtual unsigned int get_index_count()                                                     = 0;
        virtual void set_position(float x, float y)                                                = 0;
        virtual void move(float x_offset, float y_offset)                                          = 0;
        virtual void set_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) = 0;
        virtual void move_color(
            unsigned char r_offset, unsigned char g_offset, unsigned char b_offset, unsigned char a_offset) = 0;
    };
} // namespace kckn
