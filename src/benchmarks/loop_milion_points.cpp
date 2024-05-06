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
            object_manager->create<RandomParticle>(520, 520);
        }
    }
}

BENCHMARK_DEFINE_F(RendererFixture, BM_CreateParticlesBatch)(benchmark::State& state) {
    for (auto _ : state) {
        object_manager->create_many<RandomParticle>(1000, 520, 520);
    }
}

BENCHMARK_DEFINE_F(RendererFixture, BM_MoveRandomly)(benchmark::State& state) {
    auto points = object_manager->create_many<RandomParticle>(1000, 520, 520);
    for (auto _ : state) {
        for (auto& point : points) {
            point->move_randomly();
            benchmark::ClobberMemory();
        }
    }
}

BENCHMARK_DEFINE_F(RendererFixture, BM_UploadWholeVertexBuffer)(benchmark::State& state) {
    auto points = object_manager->create_many<RandomParticle>(1000, 520, 520);
    for (auto& point : points) {
        point->move_randomly();
    }
    object_manager->update_batch_buffers();

    for (auto _ : state) {
        object_manager->get_vertex_buffer()->upload_whole_batch_buffer();
    }
}

BENCHMARK_DEFINE_F(RendererFixture, BM_UploadWholeIndexBuffer)(benchmark::State& state) {
    auto points = object_manager->create_many<RandomParticle>(1000, 520, 520);
    for (auto& point : points) {
        point->move_randomly();
    }
    object_manager->update_batch_buffers();

    for (auto _ : state) {
        object_manager->get_index_buffer()->upload_whole_batch_buffer();
    }
}


BENCHMARK_REGISTER_F(RendererFixture, BM_CreateParticlesSingle)->Unit(benchmark::kMillisecond);
BENCHMARK_REGISTER_F(RendererFixture, BM_CreateParticlesBatch)->Unit(benchmark::kMillisecond);
BENCHMARK_REGISTER_F(RendererFixture, BM_MoveRandomly)->Unit(benchmark::kMillisecond);
BENCHMARK_REGISTER_F(RendererFixture, BM_UploadWholeVertexBuffer)->Unit(benchmark::kMillisecond);
BENCHMARK_REGISTER_F(RendererFixture, BM_UploadWholeIndexBuffer)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
