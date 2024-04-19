#pragma once
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
struct ShaderSources {
    std::string vertex_shader;
    std::string fragment_shader;
};

static unsigned int compile_shader(unsigned int type, const std::string& source) {
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

static unsigned int create_shader(const std::string& vertex_shader, const std::string& fragment_shader) {
    unsigned int program = glCreateProgram();

    // create intermediate shaders
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

    // link the shaders into the program
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    int status;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
    if (status == GL_FALSE) {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetProgramInfoLog(program, length, &length, message);
        std::cout << "Failed to validate program:" << std::endl;
        std::cout << message << std::endl;
        std::terminate();
    }
    // remove intermediaate shaders
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}
static ShaderSources read_sources_from_file(std::string filepath) {
    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];
    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
    ShaderType mode = ShaderType::NONE;
    for (std::string line; std::getline(stream, line);) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                mode = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                mode = ShaderType::FRAGMENT;
            }
            continue;
        }
        ss[(int) mode] << line << std::endl;
    }
    ShaderSources sources;
    sources.vertex_shader   = ss[(int) ShaderType::VERTEX].str();
    sources.fragment_shader = ss[(int) ShaderType::FRAGMENT].str();
    return sources;
}
