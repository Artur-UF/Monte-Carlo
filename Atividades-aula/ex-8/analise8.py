import numpy as np
import matplotlib.pyplot as plt
import scipy as sp
import sys

simx, rej, srej = np.loadtxt(sys.argv[1], unpack=True)

#simy = abs(simy - np.pi)
zoom = 1

plt.scatter(simx[zoom:], rej[zoom:], s=.6, c='g', label='Com rejeição')
plt.scatter(simx[zoom:], srej[zoom:], s=.6, c='r', label='Sem rejeição')
plt.hlines(np.pi/4, min(simx[zoom:]), max(simx[zoom:]), 'k', label=r'$\pi/4$')
plt.xlabel(r'$N$')
plt.ylabel(r'$n/N$')
#plt.ylim(np.pi/4-.05, np.pi/4+.05)
plt.grid()
plt.legend()
plt.tight_layout()
plt.savefig('plot8.png', dpi=200)


