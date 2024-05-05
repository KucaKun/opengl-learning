#pragma once
#include <map>
#include <memory>

#include "global_data.hpp"
#include "object.hpp"
#include "object_manager.hpp"
#include "shader.hpp"
#include "utils.hpp"
namespace kckn {
    class Renderer {
    private:
        std::map<std::string, std::vector<s_ptr<Shader>>> shader_register;

    public:
        Renderer();

        /// @brief Draws all objects in the object register
        void draw_all(ObjectManager& object_manager);
    };
} // namespace kckn
