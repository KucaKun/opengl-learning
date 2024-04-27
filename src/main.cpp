
#include "examples/examples.hpp"
#include "window.hpp"
using namespace kckn;
int main(void) {
    std::shared_ptr<Window> window       = std::make_shared<Window>(1080, 720);
    std::shared_ptr<Scene> current_scene = std::make_shared<PointScene>();
    while (!window->should_close()) {
        window->prepare_frame(current_scene);
        window->clear();
        if (current_scene) {
            current_scene->on_clean();
            current_scene->on_render();
            current_scene->on_imgui();
        }
        window->draw_imgui();
        window->finalize_frame();
    }
    return 0;
}
