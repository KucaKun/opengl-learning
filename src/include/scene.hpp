#pragma once
#include <memory>

#include "renderer.hpp"

namespace kckn {
    class Scene {
    protected:
        Renderer renderer;

    public:
        Scene() : renderer(){};
        virtual ~Scene(){};
        virtual void on_clean() {};
        virtual void on_render() {};
        virtual void on_imgui() {};
    };
} // namespace kckn
