import numpy as np
import matplotlib.pyplot as plt
import sys

simx, simy = np.loadtxt(sys.argv[1], unpack=True)

simy = (simy - np.pi)**2

zoom = int(len(simx)/2)
plt.scatter(simx[zoom:], simy[zoom:], s=.6, c='k')
#plt.hlines(np.pi, simx[zoom], simx[-1], color='r', linewidth=0.8, linestyles='dashed')
#plt.xscale('log')
plt.xlabel('N')
plt.ylabel(r'$(2N/n - \pi)^{2}$')
plt.grid()
plt.tight_layout()
plt.savefig('plot5.png', dpi=200)

