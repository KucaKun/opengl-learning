#pragma once
#include <GL/glew.h>
#include <functional>
#include <string>
#include <typeinfo>
#include <vector>

#include "glm/glm.hpp"
namespace kckn {
    struct ProtoUniform {
        std::string type;
        std::string name;
    };

    class Uniform {
    private:
        std::string type;
        std::string name;
        int location;
        unsigned int program_id;

    public:
        Uniform(ProtoUniform proto, unsigned int program_id);

        template <typename T, typename... A>
        void set_value(A... args) {
            if constexpr (sizeof...(args) == 1) {
                if constexpr (std::is_same_v<T, float>) {
                    glUniform1f(location, args...);
                } else if constexpr (std::is_same_v<T, double>) {
                    glUniform1d(location, args...);
                } else if constexpr (std::is_same_v<T, int>) {
                    glUniform1i(location, args...);
                } else if constexpr (std::is_same_v<T, glm::mat4>) {
                    glUniformMatrix4fv(location, 1, false, args...);
                }
            } else if constexpr (sizeof...(args) == 2) {
                if constexpr (std::is_same_v<T, float>) {
                    glUniform2f(location, args...);
                } else if constexpr (std::is_same_v<T, double>) {
                    glUniform2d(location, args...);
                } else if constexpr (std::is_same_v<T, int>) {
                    glUniform2i(location, args...);
                }
            } else if constexpr (sizeof...(args) == 3) {
                if constexpr (std::is_same_v<T, float>) {
                    glUniform3f(location, args...);
                } else if constexpr (std::is_same_v<T, double>) {
                    glUniform3d(location, args...);
                } else if constexpr (std::is_same_v<T, int>) {
                    glUniform3i(location, args...);
                }
            } else if constexpr (sizeof...(args) == 4) {
                if constexpr (std::is_same_v<T, float>) {
                    glUniform4f(location, args...);
                } else if constexpr (std::is_same_v<T, double>) {
                    glUniform4d(location, args...);
                } else if constexpr (std::is_same_v<T, int>) {
                    glUniform4i(location, args...);
                }
            }
        }

        operator int() const {
            return location;
        }
    };
} // namespace kckn
