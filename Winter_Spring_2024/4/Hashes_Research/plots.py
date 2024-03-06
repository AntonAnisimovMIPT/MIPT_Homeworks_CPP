import matplotlib.pyplot as plt
import numpy as np

# Данные из таблицы
x = [100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000, 1100000, 1200000, 1300000, 1400000, 1500000, 1600000, 1700000, 1800000, 1900000, 2000000]

RSHash = [1, 5, 8, 28, 32, 46, 54, 85, 89, 105, 125, 149, 209, 232, 235, 294, 354, 354, 424, 477]
JSHash = [4, 2, 6, 19, 33, 32, 59, 89, 85, 121, 123, 205, 193, 240, 244, 338, 338, 378, 420, 475]
PJWHash = [24, 107, 210, 364, 633, 920, 1261, 1605, 2004, 2497, 3088, 3558, 4135, 4895, 5540, 6467, 7193, 8181, 8988, 9871]
ELFHash = [24, 107, 210, 364, 633, 920, 1261, 1605, 2004, 2497, 3088, 3558, 4135, 4895, 5540, 6467, 7193, 8181, 8988, 9871]
BKDRHash = [1, 6, 10, 20, 24, 40, 56, 80, 95, 107, 141, 156, 185, 238, 244, 310, 324, 408, 441, 496]
SDBMHash = [1, 7, 7, 23, 26, 49, 59, 86, 75, 116, 129, 160, 190, 221, 275, 340, 342, 366, 458, 475]
DJBHash = [1, 7, 10, 19, 26, 33, 47, 72, 98, 112, 151, 165, 224, 228, 277, 356, 339, 347, 415, 476]
DEKHash = [3, 4, 13, 47, 46, 61, 88, 121, 151, 173, 234, 271, 315, 377, 456, 466, 554, 616, 724, 797]
APHash = [1, 4, 14, 17, 24, 52, 63, 68, 108, 110, 146, 203, 209, 243, 318, 328, 340, 368, 414, 458]

# Построение графика
plt.figure(figsize=(10, 6))
plt.plot(x, RSHash, marker='o', label='RSHash', linewidth=0.25, markersize=2)
plt.plot(x, JSHash, marker='o', label='JSHash', linewidth=0.25, markersize=2)
plt.plot(x, PJWHash, marker='o', label='PJWHash', linewidth=0.25, markersize=2)
plt.plot(x, ELFHash, marker='o', label='ELFHash', linewidth=0.25, markersize=2)
plt.plot(x, BKDRHash, marker='o', label='BKDRHash', linewidth=0.25, markersize=2)
plt.plot(x, SDBMHash, marker='o', label='SDBMHash', linewidth=0.25, markersize=2)
plt.plot(x, DJBHash, marker='o', label='DJBHash', linewidth=0.25, markersize=2)
plt.plot(x, DEKHash, marker='o', label='DEKHash', linewidth=0.25, markersize=2)
plt.plot(x, APHash, marker='o', label='APHash', linewidth=0.25, markersize=2)

plt.title('Количество коллизий для разных хэш-функций')
plt.xlabel('Количество строк ($10^5$)')
plt.ylabel('Количество коллизий')
plt.legend()
plt.grid(True)
plt.show()
