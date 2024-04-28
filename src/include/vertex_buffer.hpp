#pragma once
namespace kckn {

    struct Vertex {
        float x, y, r, g, b, a;
    };
    class VertexBuffer {
        unsigned int renderer_id;
        Vertex batch_buffer[0xffffffff / sizeof(Vertex)];

    public:
        VertexBuffer();
        ~VertexBuffer();
        void set_data(void* data, unsigned int offset, unsigned int size);
        Vertex* get_batch_buffer();
        void bind() const;
        void unbind() const;
        int get_batch_offset(int obj_id) const;
        operator unsigned int() const {
            return renderer_id;
        }
    };
} // namespace kckn
