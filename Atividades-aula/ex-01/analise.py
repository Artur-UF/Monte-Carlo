import numpy as np
import matplotlib.pyplot as plt

A11 = np.loadtxt('1684453360-N100.txt', unpack=True)
A21 = np.loadtxt('1684453363-N100.txt', unpack=True)
exato1 = np.loadtxt('exato-N100.txt', unpack=True)

A12 = np.loadtxt('1684453371-N200.txt', unpack=True)
A22 = np.loadtxt('1684453374-N200.txt', unpack=True)
exato2 = np.loadtxt('exato-N200.txt', unpack=True)

figura = plt.figure(figsize=(7, 6))

plt.subplot(211)
plt.plot(A11)
plt.plot(A21)
plt.plot(exato1, label='Solução Exata')
plt.xlabel('t')
plt.ylabel(r'$N_{A}$')
plt.legend()
plt.title('N = 100')
plt.grid()

plt.subplot(212)
plt.plot(A12)
plt.plot(A22)
plt.plot(exato2, label='Solução Exata')
plt.xlabel('t')
plt.ylabel(r'$N_{A}$')
plt.legend()
plt.title('N = 200')
plt.grid()

plt.tight_layout()
plt.savefig('plot1.png', dpi=200)
