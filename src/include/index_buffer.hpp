#pragma once
#include "utils.hpp"
namespace kckn {
    class IndexBuffer {
        unsigned int renderer_id;
        unsigned int count;
        s_ptr<unsigned int[]> batch_buffer;

    public:
        IndexBuffer();
        ~IndexBuffer();
        void set_data(unsigned int* data, unsigned int offset, unsigned int _count);
        void upload_whole_batch_buffer();
        void bind() const;
        void unbind() const;
        inline unsigned int get_count() const {
            return count;
        }
    };
} // namespace kckn
