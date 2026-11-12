# OpenMP ile Matris-Vektör Çarpımı ve Performans Analizi

Bu proje, C++ ve **OpenMP** kütüphanesi kullanılarak çoklu iş parçacığı (multi-threading) ortamlarında yoğun matris-vektör çarpımı ($y = Ax$) işleminin nasıl paralelleştirildiğini ve ölçeklendiğini gösterir[cite: 1]. Projede tek thread (seri) ve çoklu thread (paralel) yöntemler uygulanmış; farklı zamanlama (scheduling) stratejilerinin başarım ve hızlanma (speedup) oranları karşılaştırılmıştır[cite: 1].

## 🚀 Proje Özeti

Program, $3000 \times 3000$ boyutundaki rastgele oluşturulmuş bir matris ($A$) ile vektör ($x$) üzerinde çarpma işlemini iki temel yaklaşım altında gerçekleştirir[cite: 1]:

1. **Seri Hesaplama:** Tek çekirdek üzerinde referans çalışma süresini ($T_{serial}$) hesaplar[cite: 1].
2. **Paralel Hesaplama:** Belirlenen thread sayıları ($1, 2, 4, 8, 16$) üzerinden matris satırlarını thread'lere paylaştırarak çalışır[cite: 1].
3. **Analiz ve Raporlama:** Her konfigürasyon için süreyi ölçer, referans süreye göre hızlanmayı ($Speedup = T_{serial} / T_{parallel}$) hesaplar ve sonuçları konsolda tablo halinde sunar[cite: 1].

### Uygulanan Scheduling Yöntemleri

OpenMP paralel döngü mekanizmasında iş yükü dağıtımı için üç farklı strateji analiz edilir[cite: 1]:

1. **Static (`schedule(static)`):**
   - Döngü iterasyonları thread'lere derleme/çalışma anında sabit ve eşit bloklar halinde bölünür.
   - **Gözlem:** Düşük ek yük (overhead) üretir, dengeli iş yüklerinde en yüksek verimi sunar.

2. **Dynamic (`schedule(dynamic)`):**
   - İş blokları çalışma anında boşta kalan thread'lere dinamik bir iş kuyruğu üzerinden dağıtılır.
   - **Gözlem:** Her döngü iterasyonunun süresi farklı olan dengesiz yükler için uygundur; ek yükü `static`'e göre daha fazladır.

3. **Guided (`schedule(guided)`):**
   - Başlangıçta thread'lere büyük iş parçaları verilir, iterasyon ilerledikçe blok boyutları logaritmik olarak küçülür.
   - **Gözlem:** `dynamic` stratejisine göre kuyruk erişim yükünü azaltırken yük dengesini korur.

## 🛠️ Teknolojiler

* **Dil:** C++ (C++11 standardı)
* **Kütüphane:** OpenMP (`omp.h`, `libgomp`)[cite: 1]
* **Platform:** Cross-platform (Linux / Windows)

## ⚙️ Kurulum ve Çalıştırma

Kodları derlemek için OpenMP destekleyen bir C++ derleyicisine (GCC/MinGW gibi) ihtiyacınız vardır.

### Derleme

```bash
# Linux / macOS
g++ -O3 -fopenmp openmp_matrix_vector_carpim.cpp -o matrix_app

# Windows (MinGW/GCC)
g++ -O3 -fopenmp openmp_matrix_vector_carpim.cpp -o matrix_app.exe
```

### Çalıştırma

```bash
# Belirli bir thread üst sınırı ile çalıştırma (örn: 8 thread)
./matrix_app 8

# Sistemdeki tüm donanımsal mantıksal çekirdekleri kullanarak çalıştırma
./matrix_app
```
