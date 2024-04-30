#pragma once
#include <map>
#include <memory>

#include "global_register.hpp"
#include "index_buffer.hpp"
#include "object.hpp"
#include "shader.hpp"
#include "utils.hpp"
#include "vertex_array.hpp"
namespace kckn {
    class Renderer {
    private:
        std::map<std::string, std::vector<s_ptr<Shader>>> shader_register;
        std::vector<s_ptr<VertexBuffer>> vb_register;
        std::vector<s_ptr<IndexBuffer>> ib_register;
        std::vector<s_ptr<VertexArray>> va_register;
        std::vector<s_ptr<VertexBufferLayout>> layout_register;

        /// @brief A register of objects mapped by their GL_DRAW_MODE
        std::map<int, std::vector<s_ptr<Object>>> object_register;

    public:
        Renderer();

        /// Creates a new object of type T and adds it to the object register
        template <typename T, typename... A>
        s_ptr<T> create(A... args) {
            auto draw_mode = T::get_draw_mode();
            object_register[draw_mode].push_back(std::make_shared<T>(args...));
            s_ptr<T> returned = std::dynamic_pointer_cast<T>(object_register[draw_mode].back());
            return returned;
        }

        /// Creates a whole lot of objects and adds it to the register
        template <typename T, typename... A>
        std::vector<s_ptr<T>> create_many(size_t count, A... args) {
            std::vector<s_ptr<T>> subvector;
            subvector.reserve(count);
            for (size_t i = 0; i < count; i++) {
                subvector.push_back(create<T>(args...));
            }
            return subvector;
        }

        /// @brief Draws all objects in the object register
        void draw_all();
    };
} // namespace kckn
