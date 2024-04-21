#pragma once
#include <GL/glew.h>
#include <vector>
static inline unsigned int glsizeof(unsigned int gl_type_enum) {
    switch (gl_type_enum) {
    case GL_BYTE:
        return sizeof(char);
    case GL_UNSIGNED_BYTE:
        return sizeof(unsigned char);
    case GL_SHORT:
        return sizeof(short);
    case GL_UNSIGNED_SHORT:
        return sizeof(unsigned short);
    case GL_INT:
        return sizeof(int);
    case GL_UNSIGNED_INT:
        return sizeof(unsigned int);
    case GL_FLOAT:
        return sizeof(float);
    case GL_2_BYTES:
        return 2 * sizeof(char);
    case GL_3_BYTES:
        return 3 * sizeof(char);
    case GL_4_BYTES:
        return 4 * sizeof(char);
    case GL_DOUBLE:
        return sizeof(double);
    }
    return 0;
}

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    inline unsigned int get_size() {
        return glsizeof(type) * count;
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride = 0;

public:
    // VertexBufferLayout();

    inline std::vector<VertexBufferElement> get_elements() const {
        return elements;
    }

    inline unsigned int get_stride() const {
        return stride;
    }

    void push(unsigned int gl_type_enum, unsigned int count) {
        elements.push_back({gl_type_enum, count, false});
        stride += count * glsizeof(gl_type_enum);
    }
};
