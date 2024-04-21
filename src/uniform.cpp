#include "uniform.hpp"

#include <GL/glew.h>
#include <functional>
#include <string>

Uniform::Uniform(ProtoUniform proto, unsigned int program_id)
    : type(proto.type), name(proto.name), program_id(program_id) {
    location = glGetUniformLocation(program_id, name.c_str());
}
