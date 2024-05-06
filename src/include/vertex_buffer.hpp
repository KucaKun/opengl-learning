#pragma once
#include "utils.hpp"
namespace kckn {


    class VertexBuffer {
        unsigned int renderer_id;
        s_ptr<unsigned char[]> batch_buffer;

    public:
        VertexBuffer();
        ~VertexBuffer();
        void set_data(void* data, unsigned int offset, unsigned int size);
        s_ptr<unsigned char[]> get_batch_buffer();
        void bind() const;
        void unbind() const;
        void upload_whole_batch_buffer();
        operator unsigned int() const {
            return renderer_id;
        }
    };
} // namespace kckn
