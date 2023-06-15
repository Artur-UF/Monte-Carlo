import numpy as np
import matplotlib.pyplot as plt
import scipy as sp
import sys

simx, simy = np.loadtxt(sys.argv[1], unpack=True)

simy = abs(simy - np.pi)
zoom = 100 #int(len(simx)/3)

simx = np.log10(simx[zoom:])
simy = np.log10(simy[zoom:])

result = sp.stats.linregress(simx, simy)

a = result.slope
b = result.intercept

fitline = lambda x: a*x + b

zoom = 0
plt.scatter(simx[zoom:], simy[zoom:], s=.6, c='k')
plt.plot(simx[zoom:], fitline(simx)[zoom:], 'r')
plt.xlabel(r'$\log{(N)}$')
plt.ylabel(r'$\log{(\left \langle 2N/n \right \rangle - \pi)}$')
plt.xlim(2, 4)
plt.ylim(-6, -1)
plt.grid()
plt.tight_layout()
plt.savefig('plot5.png', dpi=200)

