
#include "examples/examples.hpp"
#include "scene.hpp"
#include "window.hpp"
using namespace kckn;
int main(void) {
    std::shared_ptr<Window> window    = std::make_shared<Window>(1080, 720);
    std::shared_ptr<PointScene> scene = std::make_shared<PointScene>(window);
    while (!window->should_close()) {
        window->prepare_frame();
        window->clear();

        scene->on_clean();
        scene->on_render();
        scene->on_imgui();

        window->draw_imgui();
        window->finalize_frame();
    }
    return 0;
}
