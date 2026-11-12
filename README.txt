OpenMP Matrix-Vector Multiplication Benchmark
A C++ benchmarking tool designed to measure, compare, and analyze the performance of dense matrix-vector multiplication (
y=A⋅x) using OpenMP multithreading.   
openmp_matrix_vector_carpim.cpp

The program runs a baseline serial implementation, tests parallel execution across configurable thread counts (1, 2, 4, 8, 16), and outputs performance comparison tables including execution time and speedup factors.   
openmp_matrix_vector_carpim.cpp

Technical Overview
Problem Dimension: 
3000×3000 matrix size by default (
M=3000,N=3000).   
openmp_matrix_vector_carpim.cpp

Memory Layout: 1D contiguous dynamically allocated vector (std::vector<double>) mapped as a 2D matrix via the row-major index macro MAT_ACCESS(A, i, j, N).   
openmp_matrix_vector_carpim.cpp

Parallelization Strategy: Data parallelism applied over the outer loop (
M rows) using OpenMP #pragma omp parallel for.   
openmp_matrix_vector_carpim.cpp

Metrics Tracked: Wall-clock execution time via std::chrono::high_resolution_clock and relative speedup (
S= 
T 
parallel
​
 
T 
serial
​
 
​
 ).   
openmp_matrix_vector_carpim.cpp

Note on Scheduling: While the benchmark loop iterates through labels static, dynamic, and guided, the OpenMP directive in run_test is currently hardcoded to schedule(static). To dynamically evaluate different OpenMP schedules at runtime, update the pragma to schedule(runtime) and call omp_set_schedule() accordingly.   
openmp_matrix_vector_carpim.cpp

Prerequisites
C++ Compiler: GCC (g++) 
≥ 7.0 or Clang with OpenMP support.

OpenMP Runtime Library: Typically bundled with standard GCC distributions (libgomp).

Compilation
Compile using g++ with the -fopenmp flag and -O3 optimization:

Bash
g++ -O3 -fopenmp openmp_matrix_vector_carpim.cpp -o matvec_benchmark
Usage
Run with the default maximum hardware threads detected automatically:

Bash
./matvec_benchmark
Or pass the maximum number of threads as a command-line argument:

Bash
# Benchmark up to 8 threads
./matvec_benchmark 8
If the specified or hardware-detected thread count is lower than 16, higher thread count tiers (e.g., 8, 16) are pruned automatically.   
openmp_matrix_vector_carpim.cpp

Sample Output
Plaintext
Matris Boyutu: 3000x3000
---------------------------------------
Seri Calisma Suresi (T_serial): 0.018230 s
---------------------------------------
Paralel Testler Basliyor...

--- Schedule: static ---
  Threads: 1, Sure: 0.018150 s, Speedup: 1.004408
  Threads: 2, Sure: 0.009420 s, Speedup: 1.935244
  Threads: 4, Sure: 0.005110 s, Speedup: 3.567515
  Threads: 8, Sure: 0.003250 s, Speedup: 5.609231

### Tablo: Calisma Sureleri (s) ###
---------------------------------------------------------
  Thread Sayisi         static        dynamic         guided
---------------------------------------------------------
              1       0.018150       0.018140       0.018160
              2       0.009420       0.009450       0.009410
              4       0.005110       0.005130       0.005090
              8       0.003250       0.003280       0.003240
---------------------------------------------------------

### Tablo: Speedup Degerleri ###
(T_serial = 0.018230 s)
---------------------------------------------------------
  Thread Sayisi         static        dynamic         guided
---------------------------------------------------------
              1       1.004408       1.004961       1.003855
              2       1.935244       1.929101       1.937301
              4       3.567515       3.553606       3.581532
              8       5.609231       5.557927       5.626543
---------------------------------------------------------
