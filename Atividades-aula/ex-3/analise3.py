import numpy as np
import matplotlib.pyplot as plt
import sys

path = sys.argv[1]

simx, simy = np.loadtxt(path, unpack=True)
exatox, exatoy = np.loadtxt('bin100.dat', unpack=True)

zoom = 30
plt.scatter(simx[zoom:-zoom], simy[zoom:-zoom], s=3, c='k', label='Simulação')
plt.plot(exatox[zoom:-zoom], exatoy[zoom:-zoom], linewidth=.8, label='Binomial')
plt.legend()
plt.xlabel('n(Bolas)')
plt.ylabel('p(n)')
plt.grid()
plt.savefig('plot3.png', dpi=200)
