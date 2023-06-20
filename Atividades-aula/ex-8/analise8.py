import numpy as np
import matplotlib.pyplot as plt
import sys

simx, rej, srej = np.loadtxt(sys.argv[1]+'/dinamica.dat', unpack=True)

#simy = abs(simy - np.pi)
zoom = 1

plt.scatter(simx[zoom:], rej[zoom:], s=.3, c='g', label='Com rejeição')
plt.scatter(simx[zoom:], srej[zoom:], s=.3, c='r', label='Sem rejeição')
plt.hlines(np.pi/4, min(simx[zoom:]), max(simx[zoom:]), 'k', label=r'$\pi/4$')
plt.xlabel(r'$N$')
plt.ylabel(r'$n/N$')
plt.ylim(.4, .83)
plt.xlim(simx[zoom], simx[-1])
plt.grid()
plt.legend()
plt.tight_layout()
plt.savefig(sys.argv[1]+'/simulacao.png', dpi=200)

