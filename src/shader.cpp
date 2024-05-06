#include "shader.hpp"

#include <GL/glew.h>
#include <format>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "glm/gtc/matrix_transform.hpp"
#include "global_data.hpp"
#include "utils.hpp"
using namespace kckn;

Shader::Shader(ShaderSources sources) {
    parse_from_string(sources);
    create_program();
}

Shader::Shader(std::string _filename) : filename(_filename) {
    parse_from_file(_filename);
    create_program();
}


void Shader::parse_from_file(std::string& filename) {
    std::ifstream stream(filename);
    std::stringstream sources_stream;
    sources_stream << stream.rdbuf();
    parse_from_stream(sources_stream);
}

void Shader::parse_from_string(ShaderSources& sources) {
    std::stringstream sources_stream;
    sources_stream << "#shader vertex\n";
    sources_stream << sources.vertex_shader;
    sources_stream << "#shader fragment\n";
    sources_stream << sources.fragment_shader;
    parse_from_stream(sources_stream);
}

void Shader::parse_from_stream(std::stringstream& stream) {
    enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };
    ShaderType mode = ShaderType::NONE;

    std::stringstream source_code[2];
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
        if (mode == ShaderType::NONE) {
            continue;
        }
        // parsing uniforms
        if (line.find("uniform") != std::string::npos) {
            std::string stripped_line           = strip_string(line);
            std::vector<std::string> split_line = split_string(stripped_line, " ");
            if (split_line.size() == 3) {
                ProtoUniform u{split_line[1], split_line[2].replace(split_line[2].end() - 1, split_line[2].end(), "")};
                proto_uniforms.push_back(u);
            }
        }

        // parsing source code
        source_code[(int) mode] << line << std::endl;
    }
    sources.vertex_shader   = source_code[(int) ShaderType::VERTEX].str();
    sources.fragment_shader = source_code[(int) ShaderType::FRAGMENT].str();
}

void Shader::create_program() {
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
        std::cout << "Failed to validate shader program." << std::endl;
        std::cout << message << std::endl;
        std::terminate();
    }
    // remove intermediaate shaders
    glDeleteShader(vs);
    glDeleteShader(fs);

    // locate and remember uniforms
    for (auto& proto_uniform : proto_uniforms) {
        uniforms.emplace(proto_uniform.name, Uniform(proto_uniform, renderer_id));
    }
}

void Shader::set_default_uniforms() {
    bind();
    if (uniforms.contains("u_mvp")) {
        glm::mat4 mvp =
            glm::ortho(0.0f, (float) global_data.window_width, 0.0f, (float) global_data.window_height, -1.0f, 1.0f);
        set_uniform<glm::mat4>("u_mvp", &mvp[0][0]);
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
