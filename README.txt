# OpenMP Matrix-Vector Multiplication Benchmark & Performance Analysis

A performance analysis and benchmarking tool developed in C++ using **OpenMP** to evaluate and compare the execution performance of dense matrix-vector multiplication ($y = Ax$) in serial versus parallel implementations[cite: 1].

The program benchmarks execution times across various thread counts and OpenMP scheduling strategies (`static`, `dynamic`, `guided`), calculates speedup factors relative to the serial baseline, and outputs formatted summary tables directly to the console[cite: 1].

---

## 📌 Key Features

- **Dynamic Thread Scaling:** Automatically identifies the system's maximum supported threads or scales based on a command-line upper limit ($1, 2, 4, 8, 16$)[cite: 1].
- **Work Scheduling Evaluation:**
  - `static`: Iterations are divided into equal-sized chunks assigned to threads before execution.
  - `dynamic`: Idle threads pull loop chunks from a shared queue at runtime (ideal for non-uniform workloads).
  - `guided`: Chunks start large and decrease exponentially in size over time.
- **High-Precision Profiling:** Wall-clock execution times are measured with microsecond accuracy via `std::chrono::high_resolution_clock`[cite: 1].
- **Formatted Terminal Reports:** Outputs execution durations and relative speedups in clean ASCII tables[cite: 1].

---

## 🛠️ Prerequisites

- **C++ Compiler:** GCC (`g++`) $\ge 9.0$ or Clang (supporting C++11 standard)
- **OpenMP Runtime:** OpenMP compiler support must be enabled (`libgomp`).

---

## ⚙️ Compilation

Compile with the `-fopenmp` flag to enable OpenMP and `-O3` for optimal loop vectorization:

### Linux / macOS
```bash
g++ -O3 -fopenmp main.cpp -o matrix_app
```

### Windows (MinGW-w64)
```powershell
g++ -O3 -fopenmp main.cpp -o matrix_app.exe
```

---

## 🚀 Usage

Optionally pass the maximum number of threads as a command-line argument[cite: 1]:

```bash
# Run tests up to a maximum of 8 threads:
./matrix_app 8

# Run with all available logical cores detected by the system:
./matrix_app
```

---

## 📊 Sample Output

```text
Matris Boyutu: 3000x3000
---------------------------------------
Seri Calisma Suresi (T_serial): 0.018240 s
---------------------------------------
Paralel Testler Basliyor...

--- Schedule: static ---
  Threads: 1, Sure: 0.018150 s, Speedup: 1.004959
  Threads: 2, Sure: 0.009410 s, Speedup: 1.938363
  Threads: 4, Sure: 0.005120 s, Speedup: 3.562500
  Threads: 8, Sure: 0.003210 s, Speedup: 5.682243

### Tablo: Calisma Sureleri (s) ###
---------------------------------------------------------
  Thread Sayisi         static        dynamic         guided
---------------------------------------------------------
              1       0.018150       0.018200       0.018180
              2       0.009410       0.009850       0.009520
              4       0.005120       0.005430       0.005210
              8       0.003210       0.003580       0.003340
---------------------------------------------------------

### Tablo: Speedup Degerleri ###
(T_serial = 0.018240 s)
---------------------------------------------------------
  Thread Sayisi         static        dynamic         guided
---------------------------------------------------------
              1       1.004959       1.002198       1.003300
              2       1.938363       1.851777       1.915966
              4       3.562500       3.359116       3.500960
              8       5.682243       5.094972       5.461078
---------------------------------------------------------
```
