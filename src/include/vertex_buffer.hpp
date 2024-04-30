#pragma once
namespace kckn {

    struct Position {
        float x, y;
    };
    struct Color {
        float r, g, b, a;
    };
    union Vertex {
        float data[6];
        struct {
            Position position;
            Color color;
        };
    };

    class VertexBuffer {
        unsigned int renderer_id;

    public:
        VertexBuffer();
        ~VertexBuffer();
        void set_data(void* data, unsigned int offset, unsigned int size);
        void bind() const;
        void unbind() const;
        int get_batch_offset(int obj_id) const;
        operator unsigned int() const {
            return renderer_id;
        }
    };
} // namespace kckn
