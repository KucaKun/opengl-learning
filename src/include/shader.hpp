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
        std::vector<ProtoUniform> proto_uniforms;
        std::map<std::string, Uniform> uniforms;
        unsigned int renderer_id;
        ShaderSources sources;
        std::string filename;
        unsigned int compile_shader(unsigned int type, const std::string& source);

    public:
        Shader(std::string filename);
        Shader(ShaderSources sources);
        void parse_from_file(std::string& filename);
        void parse_from_string(ShaderSources& sources);
        void parse_from_stream(std::stringstream& sources_stream);
        void create_program();
        void bind() const;
        void unbind() const;

        template <typename T, typename... A>
        void set_uniform(std::string uniform_name, A... args) {
            if (uniforms.contains(uniform_name)) {
                uniforms.at(uniform_name).set_value<T>(args...);
            } else {
                throw std::runtime_error(
                    std::format("uniform {} does not exist in shader code {}", uniform_name, filename));
            }
        }
    };
} // namespace kckn
