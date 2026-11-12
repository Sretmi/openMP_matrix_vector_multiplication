# OpenMP Matrix-Vector Multiplication Benchmark & Performance Analysis

C++ ve **OpenMP** kullanılarak yoğun matris-vektör çarpımı ($y = Ax$) işleminin tek çekirdek (seri) ve çok çekirdek (paralel) başarımını karşılaştıran bir analiz ve benchmark aracıdır.

Proje; farklı iş parçacığı (thread) sayıları ve OpenMP iş zamanlama stratejileri (`static`, `dynamic`, `guided`) altında çalışma sürelerini ölçer, seri referans süreye göre hızlanma (**Speedup**) oranlarını hesaplar ve sonuçları konsolda biçimlendirilmiş tablolar halinde sunar.

---

## 📌 Temel Özellikler

- **Dinamik Thread Ölçekleme:** Donanımın desteklediği maksimum thread sayısını otomatik tespit eder veya komut satırından girilen üst sınıra göre ölçeklenir ($1, 2, 4, 8, 16$).
- **İş Zamanlama (Scheduling) Karşılaştırması:** 
  - `static`: Döngü iterasyonlarının thread'lere derleme/çalışma anında eşit bloklar halinde bölünmesi.
  - `dynamic`: Boşa çıkan thread'lerin sıradaki iş bloğunu çalışma anında havuzdan çekmesi (dengesiz yükler için).
  - `guided`: Başlangıçta büyük, sonlara doğru azalan parça boyutlarıyla iş dağıtımı.
- **Hassas Zaman Ölçümü:** Süre ölçümleri `std::chrono::high_resolution_clock` ile mikrosaniye/saniye hassasiyetinde yapılır.
- **Biçimlendirilmiş Metrik Çıktısı:** Süre ve Speedup değerlerini iki ayrı karşılaştırmalı ASCII tablosunda raporlar.

---

## 🛠️ Gereksinimler

- **C++ Derleyicisi:** GCC (`g++`) $\ge 9.0$ veya Clang (C++11 standardı desteği)
- **OpenMP Kütüphanesi:** Derleyicinizin OpenMP desteği aktif olmalıdır (`libgomp`).

---

## ⚙️ Derleme

Derleme sırasında OpenMP desteğini açmak için `-fopenmp` ve optimum döngü vektörizasyonu için `-O3` optimizasyon bayrağını kullanın:

### Linux / macOS
```bash
g++ -O3 -fopenmp main.cpp -o matrix_app
```

### Windows (MinGW-w64)
```powershell
g++ -O3 -fopenmp main.cpp -o matrix_app.exe
```

---

## 🚀 Kullanım

Uygulama isteğe bağlı olarak maksimum kullanılacak thread sayısını komut satırı argümanı olarak alır:

```bash
# Maksimum 8 thread kullanacak şekilde çalıştırma:
./matrix_app 8

# Argüman verilmezse sistemdeki tüm mantıksal çekirdekleri kullanır:
./matrix_app
```

---

## 📊 Örnek Çıktı

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
              2       1.938363       1.85177
