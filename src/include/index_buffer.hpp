#pragma once
class IndexBuffer {
    unsigned int renderer_id;
    unsigned int count;

public:
    IndexBuffer(void* data, unsigned int count);
    ~IndexBuffer();
    void bind() const;
    void unbind() const;
    inline unsigned int get_count() const {
        return count;
    }
};
