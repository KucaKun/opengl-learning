#pragma once
#include <memory>

#include "renderer.hpp"
#include "window.hpp"

namespace kckn {
    class Scene {
    protected:
        Renderer renderer;
        std::shared_ptr<Window> window;

    public:
        Scene(std::shared_ptr<Window> _window) : renderer(), window(_window){};
        virtual ~Scene(){};
        virtual void on_clean() {};
        virtual void on_render() {};
        virtual void on_imgui() {};
    };
} // namespace kckn
