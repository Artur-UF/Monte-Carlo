import numpy as np
import matplotlib.pyplot as plt

simx, simy = np.loadtxt('1685476701-N100.txt', unpack=True)
exatox, exatoy = np.loadtxt('bin100.dat', unpack=True)

zoom = 30
plt.scatter(simx[zoom:-zoom], simy[zoom:-zoom], s=5, c='k', label='Simulação')
plt.plot(exatox[zoom:-zoom], exatoy[zoom:-zoom], label='Binomial')
plt.legend()
plt.xlabel('n(Bolas)')
plt.ylabel('p(n)')
plt.grid()
plt.savefig('plot3.png', dpi=200)
