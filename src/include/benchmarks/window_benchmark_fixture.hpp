#include <benchmark/benchmark.h>

#include "examples/examples.hpp"
#include "global_data.hpp"
#include "renderer.hpp"
#include "window.hpp"
namespace kckn {

    class RendererFixture : public benchmark::Fixture {
    public:
        std::unique_ptr<Window> window;
        std::unique_ptr<Renderer> renderer;
        void SetUp(::benchmark::State& state) {
            window   = std::make_unique<Window>(global_data.window_width, global_data.window_height, true);
            renderer = std::make_unique<Renderer>();
        }

        void TearDown(::benchmark::State& state) {
            window.reset();
            renderer.reset();
        }
    };

} // namespace kckn
