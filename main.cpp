#include "autogen/functions.h"

#include <benchmark/benchmark.h>
#include <stdexcept>

float fail_probability = 0;

static void bench_error_as_value(benchmark::State& state)
{
    fail_probability = state.range(0) / 100.0;
    size_t fails_total = 0;
    for (auto _ : state) {
        auto result = get_result_0();
        if (result) {
            benchmark::DoNotOptimize(*result);
        } else {
            ++fails_total;
        }
    }
    benchmark::DoNotOptimize(fails_total);
}

BENCHMARK(bench_error_as_value)->DenseRange(0, 100, 5);

static void bench_exceptions(benchmark::State& state)
{
    fail_probability = state.range(0) / 100.0;
    size_t fails_total = 0;
    for (auto _ : state) {
        try {
            benchmark::DoNotOptimize(get_result_or_throw_0());
        } catch (std::runtime_error& e) {
            ++fails_total;
        }
    }
    benchmark::DoNotOptimize(fails_total);
}

BENCHMARK(bench_exceptions)->DenseRange(0, 100, 5);

BENCHMARK_MAIN();
