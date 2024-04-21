#pragma once
#include <string>
class Texture {
private:
    unsigned int renderer_id;
    std::string file_path;
    unsigned char* local_buffer;
    int width, height, bytes_per_pixel;

public:
    Texture(const std::string& path);
    ~Texture();
    void bind(int slot) const;
    void unbind();
    inline unsigned int get_width() const {
        return width;
    }
    inline unsigned int get_height() const {
        return height;
    }
};
