#pragma once
class IndexBuffer {
    unsigned int renderer_id;

public:
    IndexBuffer(void* data, unsigned int size);
    ~IndexBuffer();
    void bind() const;
    void unbind() const;
};
