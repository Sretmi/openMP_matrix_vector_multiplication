# OpenMP Matrix-Vector Multiplication Performance Analysis

Bu proje, C++ ve **OpenMP** kütüphanesini kullanarak Matris-Vektör çarpımı ($y = Ax$) işleminin seri ve paralel performanslarını karşılaştıran bir analiz aracıdır.

Proje, farklı thread sayıları ve OpenMP zamanlama (scheduling) stratejileri (`static`, `dynamic`, `guided`) altında çalışma sürelerini ve hızlanma (speedup) oranlarını hesaplar.

## 🚀 Özellikler

* **Rastgele Veri Üretimi:** Belirtilen boyutlarda matris ve vektörler rastgele doldurulur.
* **Seri vs Paralel:** Tek thread (seri) ve çoklu thread (paralel) performans karşılaştırması.
* **OpenMP Schedule Testleri:**
    * `static`
    * `dynamic`
    * `guided`
* **Detaylı Raporlama:**
    * Her test için çalışma süresi (saniye).
    * Seri koda göre hızlanma (Speedup) oranları.
    * Tablo formatında konsol çıktısı.

## 🛠️ Gereksinimler

* **C++ Derleyicisi:** GCC (g++) önerilir.
* **OpenMP:** Derleyicinizin OpenMP desteği olmalıdır (`libgomp`).

## 💻 Derleme ve Çalıştırma

Projeyi terminal üzerinden derlemek için `-fopenmp` bayrağını kullanmalısınız.

### Linux / macOS
```bash
g++ -o matrix_app main.cpp -fopenmp -O3
./matrix_app

Windows (MinGW/GCC)
g++ -o matrix_app.exe main.cpp -fopenmp -O3
matrix_app.exe

çalıştırma
./matrix_app 8
