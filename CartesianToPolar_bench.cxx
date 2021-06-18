#include "CartesianToPolar.h"
#include <benchmark/benchmark.h>

void
precise(benchmark::State& state)
{
  double r0{ 1250 }, phi{ 1.6 };
  double r1 = r0 + 5 + 1;
  for (auto _ : state) {
    cartesian init{ r1 * std::cos(phi), r1 * std::sin(phi) };
    const int n = state.range(0);
    for (int range = 0; range < n; ++range) {
      init.x += 0.1;
      init.y += 0.1;
      polar exact = precisePol(init);
      benchmark::DoNotOptimize(&exact);
      benchmark::ClobberMemory();
    }
  }
}

BENCHMARK(precise)->RangeMultiplier(2)->Range(1024, 8192);

void
quick(benchmark::State& state)
{
  double r0{ 1250 }, phi{ 1.6 };
  double r1 = r0 + 5 + 1;
  fastCache cache{};
  for (auto _ : state) {
    cartesian init{ r1 * std::cos(phi), r1 * std::sin(phi) };
    const int n = state.range(0);
    for (int range = 0; range < n; ++range) {
      init.x += 0.1;
      init.y += 0.1;
      polar fast = fastPol(init, cache);
      benchmark::DoNotOptimize(&fast);
      benchmark::ClobberMemory();
    }
  }
}

BENCHMARK(quick)->RangeMultiplier(2)->Range(1024, 8192);

// main
BENCHMARK_MAIN();

