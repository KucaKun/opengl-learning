#pragma once

#include <format>
#include <map>
#include <vector>

#include "uniform.hpp"
namespace kckn {
    struct ShaderSources {
        std::string vertex_shader;
        std::string fragment_shader;
    };

    class Shader {
        std::map<std::string, Uniform> uniforms;
        unsigned int renderer_id;
        ShaderSources sources;
        std::string filename;

    public:
        Shader(std::string filename);

        unsigned int compile_shader(unsigned int type, const std::string& source);
        void bind() const;
        void unbind() const;

        template <typename T>
        void set_uniform(std::string uniform_name, std::vector<T> args) {
            if (uniforms.contains(uniform_name)) {
                uniforms.at(uniform_name).set_value<T>(args);
            } else {
                throw std::runtime_error(
                    std::format("uniform {} does not exist in shader code {}", uniform_name, filename));
            }
        }
    };
} // namespace kckn
