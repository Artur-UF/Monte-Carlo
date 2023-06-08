import numpy as np
import matplotlib.pyplot as plt
import sys

simx, simy = np.loadtxt(sys.argv[1], unpack=True)

#simy = (simy - np.pi)**2

zoom = 0 #int(len(simx)/1.5)
plt.scatter(simx[zoom:], simy[zoom:], s=.6, c='k')
#plt.hlines(np.pi, simx[zoom], simx[-1], color='r', linewidth=0.8, linestyles='dashed')
#plt.yscale('log')
#plt.xscale('log')
plt.xlabel('N')
plt.ylabel(r'I')
#plt.ylabel(r'$(4n/N - \pi)^{2}$')
plt.grid(True, which='both')
#plt.xlim(simx[zoom], simx[-1])
#plt.ylim(0, simy[zoom])
plt.tight_layout()
plt.savefig('plot7.png', dpi=200)

