#pragma once
namespace kckn {
    class VertexBuffer {
        unsigned int renderer_id;

    public:
        VertexBuffer(void* data, unsigned int size);
        ~VertexBuffer();
        void bind() const;
        void unbind() const;
        operator unsigned int() const {
            return renderer_id;
        }
    };
} // namespace kckn
