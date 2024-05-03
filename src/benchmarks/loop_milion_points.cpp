#include <benchmark/benchmark.h>
#include <iostream>

#include "benchmarks/window_benchmark_fixture.hpp"
#include "global_data.hpp"
#include "point.hpp"
#include "random_particle.hpp"
#include "window.hpp"
using namespace kckn;

BENCHMARK_DEFINE_F(RendererFixture, BM_CreateParticlesSingle)(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 0; i < 1000; i++) {
            renderer->object_manager.create<RandomParticle>(520, 520);
        }
    }
}

BENCHMARK_DEFINE_F(RendererFixture, BM_CreateParticlesBatch)(benchmark::State& state) {
    for (auto _ : state) {
        renderer->object_manager.create_many<RandomParticle>(1000, 520, 520);
    }
}

BENCHMARK_DEFINE_F(RendererFixture, BM_MoveRandomly)(benchmark::State& state) {
    auto points = renderer->object_manager.create_many<RandomParticle>(1000, 520, 520);
    for (auto _ : state) {
        for (auto& point : points) {
            point->move_randomly();
        }
    }
}

BENCHMARK_DEFINE_F(RendererFixture, BM_UpdateBatchBuffers)(benchmark::State& state) {

    auto points = renderer->object_manager.create_many<RandomParticle>(1000, 520, 520);
    for (auto _ : state) {
        for (auto& point : points) {
            point->move_randomly();
        }
        renderer->object_manager.update_batch_buffers();
    }
}

BENCHMARK_REGISTER_F(RendererFixture, BM_CreateParticlesSingle)->Unit(benchmark::kMillisecond);
BENCHMARK_REGISTER_F(RendererFixture, BM_CreateParticlesBatch)->Unit(benchmark::kMillisecond);
BENCHMARK_REGISTER_F(RendererFixture, BM_MoveRandomly)->Unit(benchmark::kMillisecond);
BENCHMARK_REGISTER_F(RendererFixture, BM_UpdateBatchBuffers)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
