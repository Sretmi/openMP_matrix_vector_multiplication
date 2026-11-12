# OpenMP Matrix-Vector Multiplication & Performance Analysis

A multi-threaded benchmarking tool developed in C++ using OpenMP to analyze, implement, and compare dense matrix-vector multiplication ($y = A \cdot x$) across sequential and parallel execution paradigms.

The program benchmarks standard serial execution against multi-threaded OpenMP implementations, evaluating execution durations, scheduling strategies, and computational speedup across varying thread counts[cite: 1].

---

## 📌 Computational Workflow

The program allocates a dense matrix $A$ of size $3000 \times 3000$ and vectors $x$ and $y$ using contiguous memory representations (`std::vector<double>`), executing through the following stages[cite: 1]:

1. **Data Initialization:** Fills matrix $A$ and vector $x$ with randomly generated numerical values[cite: 1]. Elements are accessed via row-major index mapping using the `MAT_ACCESS(A, i, j, N)` macro[cite: 1].
2. **Serial Baseline:** Computes $y[i] = \sum_{j=0}^{N-1} A[i][j] \cdot x[j]$ sequentially on a single thread to establish the baseline execution time ($T_{serial}$)[cite: 1].
3. **Parallel Computation:** Distributes the outer row loop among worker threads using OpenMP work-sharing directives (`#pragma omp parallel for`) across specified thread counts[cite: 1].
4. **Performance Tabulation:** Aggregates runtimes and speedup metrics ($S = \frac{T_{serial}}{T_{parallel}}$) into comparative Markdown-style console tables[cite: 1].

---

## ⚙️ Scheduling Strategies

The benchmark evaluates work-sharing behavior across three standard OpenMP loop scheduling policies[cite: 1]:

### 1. Static Scheduling (`schedule(static)`)
- **Mechanism:** Iterations are divided into equal-sized chunks and distributed statically among threads before execution begins[cite: 1].
- **Trade-offs:** Minimal scheduling and runtime overhead; optimal for homogeneous workloads where each row computation requires identical operations[cite: 1].

### 2. Dynamic Scheduling (`schedule(dynamic)`)
- **Mechanism:** Iterations are divided into chunks and assigned to threads dynamically at runtime as they complete previous assignments[cite: 1].
- **Trade-offs:** Better load balancing for irregular or unpredictable workloads, but introduces higher synchronization and dispatch overhead[cite: 1].

### 3. Guided Scheduling (`schedule(guided)`)
- **Mechanism:** Work chunks are assigned dynamically with exponentially decreasing chunk sizes over time down to a minimum threshold[cite: 1].
- **Trade-offs:** Provides an adaptive balance between the low overhead of static scheduling and the load-balancing properties of dynamic scheduling[cite: 1].

---

## 🛠️ Prerequisites

- **C++ Compiler:** GCC (`g++`) $\ge 9.0$ or Clang with OpenMP support enabled
- **OpenMP Runtime Library:** `libgomp` (bundled with standard GCC distributions)[cite: 1]

---

## 💻 Compilation & Execution

Compile the source code using the `-fopenmp` flag and `-O3` compiler optimization:

### Build
```bash
# Linux / macOS
g++ -O3 -fopenmp openmp_matrix_vector_carpim.cpp -o matvec_app

# Windows (MinGW-w64)
g++ -O3 -fopenmp openmp_matrix_vector_carpim.cpp -o matvec_app.exe
