import numpy as np
import matplotlib.pyplot as plt
import sys

N, xrej, yrej, xsrej, ysrej = np.loadtxt(sys.argv[1]+'/tracker.dat', unpack=True)


plt.scatter(xrej, yrej, s=0.4)
plt.plot(np.linspace(0, 1, 100), np.sqrt(1-np.linspace(0, 1, 100)**2), 'r')
plt.xlim(0, 1)
plt.ylim(0, 1)
plt.tight_layout()
plt.savefig(sys.argv[1]+'/walk.png', dpi=200)


