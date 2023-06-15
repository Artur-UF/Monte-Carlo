import numpy as np
import matplotlib.pyplot as plt
import scipy as sp
import sys

simx, simy = np.loadtxt(sys.argv[1], unpack=True)

zoom = 1000
plt.scatter(simx[zoom:], simy[zoom:], s=.6, c='k')
plt.xlabel(r'$N$')
plt.ylabel(r'$\left \langle n/N \right \rangle$')
plt.yticks(np.linspace(max(simy[zoom:]), min(simy[zoom:]), 10))
plt.grid()
plt.tight_layout()
plt.savefig('plot7.png', dpi=200)

