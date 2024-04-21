#include "shader.hpp"

#include <GL/glew.h>
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "utils.hpp"

Shader::Shader(std::string filename) : filename(filename) {
    std::ifstream stream(filename);
    std::string line;
    std::stringstream ss[2];
    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
    ShaderType mode = ShaderType::NONE;
    std::vector<ProtoUniform> _uniforms;

    for (std::string line; std::getline(stream, line);) {
        // parsing which type of shader it is
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                mode = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                mode = ShaderType::FRAGMENT;
            }
            continue;
        }

        // parsing uniforms
        if (line.find("uniform") != std::string::npos) {
            std::vector<std::string> split_line = split_string(line, " ");
            if (split_line.size() == 3) {
                ProtoUniform u{split_line[1], split_line[2].replace(split_line[2].end() - 1, split_line[2].end(), "")};
                _uniforms.push_back(u);
            }
        }

        // parsing source code
        ss[(int) mode] << line << std::endl;
    }

    sources.vertex_shader   = ss[(int) ShaderType::VERTEX].str();
    sources.fragment_shader = ss[(int) ShaderType::FRAGMENT].str();

    renderer_id = glCreateProgram();

    // create intermediate shaders
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, sources.vertex_shader);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, sources.fragment_shader);

    // link the shaders into the program
    glAttachShader(renderer_id, vs);
    glAttachShader(renderer_id, fs);
    glLinkProgram(renderer_id);
    glValidateProgram(renderer_id);
    int status;
    glGetProgramiv(renderer_id, GL_VALIDATE_STATUS, &status);
    if (status == GL_FALSE) {
        int length;
        glGetProgramiv(renderer_id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetProgramInfoLog(renderer_id, length, &length, message);
        std::cout << "Failed to validate program:" << std::endl;
        std::cout << message << std::endl;
        std::terminate();
    }
    // remove intermediaate shaders
    glDeleteShader(vs);
    glDeleteShader(fs);

    // locate and remember uniforms
    for (auto& proto_uniform : _uniforms) {
        uniforms.emplace(proto_uniform.name, Uniform(proto_uniform, renderer_id));
    }
}

unsigned int Shader::compile_shader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile shader:" << std::endl;
        std::cout << source << std::endl;

        std::cout << "Message:" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        std::terminate();
    }
    return id;
}

void Shader::bind() const {
    glUseProgram(renderer_id);
}
void Shader::unbind() const {
    glDeleteProgram(renderer_id);
}
