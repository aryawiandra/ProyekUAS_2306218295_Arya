/*
    Program: Discrete Fourier Transform (DFT) Sinyal 1D
    Nama    : Muhammad Arya Wiandra Utomo
    NPM     : 2306218295
    Deskripsi:
        Program ini mengimplementasikan metode numerik Discrete Fourier Transform (DFT)
        untuk menganalisis spektrum frekuensi dari data sinyal diskrit.
        Hasil transformasi disimpan ke file CSV untuk divisualisasikan.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Mendefinisikan konstanta PI
#define PI 3.14159265358979323846

// Fungsi untuk melakukan DFT pada sinyal input
void DFT(double* x, int N, double* X_real, double* X_imag, double* X_mag) {
    for (int k = 0; k < N; k++) {
        X_real[k] = 0;
        X_imag[k] = 0;
        for (int n = 0; n < N; n++) {
            X_real[k] += x[n] * cos(2 * PI * k * n / N);
            X_imag[k] -= x[n] * sin(2 * PI * k * n / N);
        }
        X_mag[k] = sqrt(X_real[k] * X_real[k] + X_imag[k] * X_imag[k]);
    }
}

int main() {
    // Contoh data sinyal (misal: kombinasi dua frekuensi)
    int N = 16;
    double x[16];
    for (int n = 0; n < N; n++) {
        // Sinyal: kombinasi dua sinus (2Hz dan 4Hz)
        x[n] = sin(2 * PI * 2 * n / N) + 0.5 * sin(2 * PI * 4 * n / N);
    }

    // Alokasi array untuk hasil DFT
    double* X_real = (double*)calloc(N, sizeof(double));
    double* X_imag = (double*)calloc(N, sizeof(double));
    double* X_mag  = (double*)calloc(N, sizeof(double));

    // Proses DFT
    DFT(x, N, X_real, X_imag, X_mag);

    // Simpan hasil ke file CSV untuk visualisasi
    FILE* fout = fopen("dft_output.csv", "w");
    if (fout == NULL) {
        printf("Gagal membuat file output\n");
        return 1;
    }
    fprintf(fout, "k,Real,Imag,|X(k)|\n");
    for (int k = 0; k < N; k++) {
        fprintf(fout, "%d,%.5f,%.5f,%.5f\n", k, X_real[k], X_imag[k], X_mag[k]);
    }
    fclose(fout);

    printf("DFT selesai. Hasil disimpan di dft_output.csv\n");

    // Free memory
    free(X_real);
    free(X_imag);
    free(X_mag);

    return 0;
}