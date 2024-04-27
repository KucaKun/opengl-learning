#pragma once
namespace kckn {
    class IndexBuffer {
        unsigned int renderer_id;
        unsigned int count;
        unsigned int batch_buffer[0xffff / sizeof(unsigned int)];

    public:
        IndexBuffer();
        ~IndexBuffer();
        void set_data(void* data, unsigned int offset, unsigned int _count);
        void bind() const;
        void unbind() const;
        inline unsigned int get_count() const {
            return count;
        }
    };
} // namespace kckn
