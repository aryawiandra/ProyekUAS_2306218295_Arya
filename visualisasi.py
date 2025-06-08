import numpy as np
import matplotlib.pyplot as plt

# Konstanta
PI = np.pi

# Fungsi untuk menghitung DFT secara manual
def DFT(x):
    N = len(x)
    X_real = np.zeros(N)
    X_imag = np.zeros(N)
    X_mag  = np.zeros(N)
    for k in range(N):
        for n in range(N):
            angle = 2 * PI * k * n / N
            X_real[k] += x[n] * np.cos(angle)
            X_imag[k] -= x[n] * np.sin(angle)
        X_mag[k] = np.sqrt(X_real[k]**2 + X_imag[k]**2)
    return X_real, X_imag, X_mag

# Parameter sinyal
N = 16
n = np.arange(N)
# Sinyal: kombinasi 2Hz dan 4Hz komponen
x = np.sin(2 * PI * 2 * n / N) + 0.5 * np.sin(2 * PI * 4 * n / N)

# Hitung DFT
X_real, X_imag, X_mag = DFT(x)

# Simpan ke CSV (opsional)
import pandas as pd
df = pd.DataFrame({
    'k': np.arange(N),
    'Real': X_real,
    'Imag': X_imag,
    '|X(k)|': X_mag
})
df.to_csv('dft_output.csv', index=False)

# Visualisasi spektrum magnitudo
plt.figure(figsize=(8, 4))
plt.stem(np.arange(N), X_mag, basefmt=" ")
plt.title('Magnitudo DFT')
plt.xlabel('Frekuensi k')
plt.ylabel('|X(k)|')
plt.grid(True)
plt.tight_layout()
plt.show()
