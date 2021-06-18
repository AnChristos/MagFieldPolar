# MagFieldPolar
Playground for avoiding atan2 calculations

# If you do not have already google benchmark installed

``git clone https://github.com/google/benchmark.git``

The following script from this repo will install the benchmark under ``${HOME}/.local``

``source buildGoogleBenchmark.sh``

# Install  getB-SIMD

``git clone https://github.com/AnChristos/MagFieldPolar``

``mkdir build; cd build``

``cmake ../MagFieldPolar``

``cmake``

# Example 

``./MagFieldPolar_test --benchmark_report_aggregates_only=true --benchmark_repetitions=20``

