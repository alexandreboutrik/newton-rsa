#include <iostream>
#include <iterator>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>
#include <benchmark/benchmark.h>

#include "rsa.hpp"
#include "metodos.hpp"

using namespace std;
using namespace boost::multiprecision;

vector<cpp_int> benchmark_values = {
    cpp_int("1000000007"), cpp_int("1000000009"), cpp_int("1000000021"), cpp_int("1000000033"),
    cpp_int("1000000087"), cpp_int("1000000093"), cpp_int("1000000097"), cpp_int("1000000103"),
    cpp_int("1000000123"), cpp_int("1000000181"), cpp_int("1000000207"), cpp_int("1000000223"),
    cpp_int("1000000241"), cpp_int("1000000271"), cpp_int("1000000289"), cpp_int("1000000297"),
    cpp_int("1000000321"), cpp_int("1000000349"), cpp_int("1000000363"), cpp_int("1000000403"),
    cpp_int("1000000409"), cpp_int("1000000411"), cpp_int("1000000427"), cpp_int("1000000433"),
    cpp_int("1000000439"), cpp_int("1000000447"), cpp_int("1000000453"), cpp_int("1000000459"),
    cpp_int("1000000483"), cpp_int("1000000513"), cpp_int("1000000531"), cpp_int("1000000579"),
    cpp_int("1000000607"), cpp_int("1000000613"), cpp_int("1000000637"), cpp_int("1000000663"),
    cpp_int("1000000711"), cpp_int("1000000753"), cpp_int("1000000787"), cpp_int("1000000801"),
    cpp_int("1000000829"), cpp_int("1000000861"), cpp_int("1000000871"), cpp_int("1000000891"),
    cpp_int("1000000901"), cpp_int("1000000919"), cpp_int("1000000931"), cpp_int("1000000933"),
    cpp_int("1000000993"), cpp_int("1000001011"), cpp_int("1000001021"), cpp_int("1000001053"),
    cpp_int("1000001087"), cpp_int("1000001099"), cpp_int("1000001137"), cpp_int("1000001161"),
    cpp_int("1000001203"), cpp_int("1000001213"), cpp_int("1000001237"), cpp_int("1000001263"),
    cpp_int("1000001269"), cpp_int("1000001273"), cpp_int("1000001279"), cpp_int("1000001311"),
    cpp_int("1000001329"), cpp_int("1000001333"), cpp_int("1000001351"), cpp_int("1000001371"),
    cpp_int("1000001393"), cpp_int("1000001413"), cpp_int("1000001447"), cpp_int("1000001449"),
    cpp_int("1000001491"), cpp_int("1000001501"), cpp_int("1000001531"), cpp_int("1000001537"),
    cpp_int("1000001539"), cpp_int("1000001581"), cpp_int("1000001617"), cpp_int("1000001621"),
    cpp_int("1000001633"), cpp_int("1000001647"), cpp_int("1000001663"), cpp_int("1000001677"),
    cpp_int("1000001699"), cpp_int("1000001759"), cpp_int("1000001773"), cpp_int("1000001789"),
    cpp_int("1000001791"), cpp_int("1000001801"), cpp_int("1000001803"), cpp_int("1000001819"),
    cpp_int("1000001857"), cpp_int("1000001887"), cpp_int("1000001917"), cpp_int("1000001927"),
    cpp_int("1000001957"), cpp_int("1000001963"), cpp_int("1000001969"), cpp_int("1000002043")
};

static void BM_eea(benchmark::State& state) {

  cpp_int p = benchmark_values[state.range(0)];
  cpp_int q = benchmark_values[state.range(1)];

  cpp_int phi_var = (p - 1) * (q - 1);

  cpp_int e = handle_nullopt(generate_e(phi_var), "'generate_e'");

  for (auto _ : state)
    benchmark::DoNotOptimize(fet(e, phi_var));
}


size_t benchmark_size = benchmark_values.size() - 1;

static void RegisterBenchmarks() {

  for (int i = 0; i < benchmark_size ; i += 2)
    benchmark::RegisterBenchmark("BM_eea", (BM_eea))->Args({i, i+1})->Threads(1);
}

static bool reg = (RegisterBenchmarks(), true);

BENCHMARK_MAIN();
