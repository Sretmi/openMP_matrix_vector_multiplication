#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <omp.h>
#include <algorithm> 
#include <map>       
#include <string>

using namespace std;

// Matris elemanlarına erişim
#define MAT_ACCESS(A, i, j, N) A[(i) * (N) + (j)]

// Matrisi ve vektörleri rastgele elemanlarla doldurur
void initialize_data(vector<double>& A, vector<double>& x, int M, int N) {
    for (int i = 0; i < M * N; ++i) {
        A[i] = rand() % 10;
    }
    for (int i = 0; i < N; ++i) {
        x[i] = rand() % 10;
    }
}

// Matris ve vektör çarpımları
void multiply_serial(const vector<double>& A, const vector<double>& x, vector<double>& y, int M, int N) {
    for (int i = 0; i < M; i++) {
        y[i] = 0.0;
        for (int j = 0; j < N; j++) {
            y[i] += MAT_ACCESS(A, i, j, N) * x[j];
        }
    }
}

//matris ve vektörlerin paralel 
void multiply_parallel(const vector<double>& A, const vector<double>& x, vector<double>& y, int M, int N, const string& schedule_type) {
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < M; i++) {
        y[i] = 0.0;
        for (int j = 0; j < N; j++) {
            y[i] += MAT_ACCESS(A, i, j, N) * x[j];
        }
    }
}


// çalıştırma fonksiyonu
double run_test(int M, int N, int num_threads, const string& schedule, bool is_serial, vector<double>& A, vector<double>& x, vector<double>& y) {
    
    // thread sayısı ayarlama 
    if (!is_serial) {
        omp_set_num_threads(num_threads);
    }

    auto start_time = chrono::high_resolution_clock::now();

    if (is_serial) {
        multiply_serial(A, x, y, M, N);
    } else {      
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < M; i++) {
            y[i] = 0.0;
            for (int j = 0; j < N; j++) {
                y[i] += MAT_ACCESS(A, i, j, N) * x[j];
            }
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    double duration = chrono::duration_cast<chrono::duration<double>>(end_time - start_time).count();
    
    return duration;
}


int main(int argc, char* argv[]) {
    const int M = 3000;
    const int N = 3000;
    int max_threads = 1; 
    if (argc > 1) {
        max_threads = atoi(argv[1]);
    } else {
        max_threads = omp_get_max_threads();
        cout << "Uyari: Thread sayisi arguman olarak verilmedi. Maks: " << max_threads << " kullaniliyor." << endl;
    }
    
    // 16 ya kadar thread sayıları 
    vector<int> thread_counts = {1, 2, 4, 8, 16};
    
    // 16dan düşük thread sayısında çalıştırılırsa sistem ona göre ayarlanır 
    if (max_threads < 16) {
        thread_counts.erase(
            std::remove_if(thread_counts.begin(), thread_counts.end(), 
                      [&](int t){ return t > max_threads; }), 
            thread_counts.end());
        cout << "Desteklenen maks. thread sayisi (" << max_threads << ") nedeniyle bazi testler yapilamamaktadir." << endl;
    }
    
    // Matris ve Vektorler
    vector<double> A(M * N);
    vector<double> x(N);
    vector<double> y(M); 
    
    srand(time(0));
    initialize_data(A, x, M, N);

    cout << fixed << setprecision(6);
    cout << "Matris Boyutu: " << M << "x" << N << endl;
    cout << "---------------------------------------" << endl;

    //  Seri Uygulama
    double T_serial = run_test(M, N, 1, "none", true, A, x, y);
    cout << "Seri Calisma Suresi (T_serial): " << T_serial << " s" << endl;
    cout << "---------------------------------------" << endl;

    // OpenMP ile Paralel Uygulama
    
    // Sonuclari saklamak icin yapi
    struct Result {
        double time_static = 0.0;
        double time_dynamic = 0.0;
        double time_guided = 0.0;
    };
    map<int, Result> results; // Thread sayisi -> Sonuclar

    vector<string> schedules = {"static", "dynamic", "guided"};

    cout << "Paralel Testler Basliyor..." << endl;
      
    for (const string& schedule : schedules) {
        cout << "\n--- Schedule: " << schedule << " ---" << endl;
        
        // 3 ayrı testi temsili
        for (int num_threads : thread_counts) {
            double T_parallel = run_test(M, N, num_threads, schedule, false, A, x, y);

            double speedup = T_serial / T_parallel;
            cout << "  Threads: " << num_threads << ", Sure: " << T_parallel << " s, Speedup: " << speedup << endl;

            // Sonuclari kaydetme 
            if (schedule == "static") {
                results[num_threads].time_static = T_parallel;
            } else if (schedule == "dynamic") {
                results[num_threads].time_dynamic = T_parallel;
            } else if (schedule == "guided") {
                results[num_threads].time_guided = T_parallel;
            }
        }
    }


    // Performans Analizi
    cout << "\n\n### Tablo: Calisma Sureleri (s) ###" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << setw(15) << "Thread Sayisi" << setw(15) << "static" << setw(15) << "dynamic" << setw(15) << "guided" << endl;
    cout << "---------------------------------------------------------" << endl;

    for (int t : thread_counts) {
        cout << setw(15) << t 
             << setw(15) << results[t].time_static 
             << setw(15) << results[t].time_dynamic 
             << setw(15) << results[t].time_guided << endl;
    }
    cout << "---------------------------------------------------------" << endl;

    
    cout << "\n\n### Tablo: Speedup Degerleri ###" << endl;
    cout << "(T_serial = " << T_serial << " s)" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << setw(15) << "Thread Sayisi" << setw(15) << "static" << setw(15) << "dynamic" << setw(15) << "guided" << endl;
    cout << "---------------------------------------------------------" << endl;

    for (int t : thread_counts) {
        double speedup_static = T_serial / results[t].time_static;
        double speedup_dynamic = T_serial / results[t].time_dynamic;
        double speedup_guided = T_serial / results[t].time_guided;
        
        cout << setw(15) << t 
             << setw(15) << speedup_static
             << setw(15) << speedup_dynamic
             << setw(15) << speedup_guided << endl;
    }
    cout << "---------------------------------------------------------" << endl;

    return 0;
}