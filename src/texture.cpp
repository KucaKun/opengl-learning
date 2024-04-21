#include "texture.hpp"

#include "GL/glew.h"
#include "stb_image.h"
#include <stdexcept>

using namespace kckn;
Texture::Texture(const std::string& path)
    : renderer_id(0), local_buffer(nullptr), width(0), height(0), bytes_per_pixel(0) {
    stbi_set_flip_vertically_on_load(1);
    local_buffer = stbi_load(path.c_str(), &width, &height, &bytes_per_pixel, 4);

    glGenTextures(1, &renderer_id);
    glBindTexture(GL_TEXTURE_2D, renderer_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer);
    unbind();
    if (local_buffer) {
        stbi_image_free(local_buffer);
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &renderer_id);
}

void Texture::bind(int slot) const {
    int texture_units;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units);

    if (slot > texture_units) {
        throw std::runtime_error("exceeded the possible slot count");
    }
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, renderer_id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}
