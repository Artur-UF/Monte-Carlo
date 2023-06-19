import numpy as np
import matplotlib.pyplot as plt
import scipy as sp
import sys

simx, simy, solta = np.loadtxt(sys.argv[1], unpack=True)

yp1 = abs(simy - np.pi)
zoom = 100 #int(len(simx)/3)

xp1 = np.log10(simx[zoom:])
yp1 = np.log10(yp1[zoom:])

result = sp.stats.linregress(xp1, yp1)

a = result.slope
b = result.intercept

fitline = lambda x: a*x + b

fig = plt.subplots(figsize=(8, 4))

plt.subplot(121)
plt.plot(simx, simy, 'r', linewidth=.7, label='Média')
plt.plot(simx, solta, 'b', linewidth=.7, label='Amostra')
plt.hlines(np.pi, simx[0], simx[-1], 'k', label=r'$\pi$', zorder=0)
plt.legend()
plt.xlim(0, 10000)
plt.ylim(3.05, 3.2)
plt.xlabel('N')
plt.ylabel('2N/n')
plt.grid()
plt.title('Estimativa')

plt.subplot(122)
plt.scatter(xp1[zoom:], yp1[zoom:], s=.6, c='k')
plt.plot(xp1[zoom:], fitline(xp1)[zoom:], 'r')
plt.xlabel(r'$\log{(N)}$')
plt.ylabel(r'$\log{(\left \langle 2N/n \right \rangle - \pi)}$')
plt.xlim(xp1[zoom], xp1[-1])
plt.ylim(-3.50, -1.8)
plt.grid()
plt.title('Erro')

plt.tight_layout()
plt.savefig('plot5.png', dpi=200)

