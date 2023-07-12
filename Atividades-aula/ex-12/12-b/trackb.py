import matplotlib.pyplot as plt
import sys
import numpy as np
plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})
args = sys.argv[1].split('-')
P = eval(args[1])
L = eval(args[3])

x, y = np.loadtxt(sys.argv[1]+'/track.dat', unpack=True)

plt.plot(x, y, c='r', linewidth=.4)
#plt.scatter(x[::N-1], y[::N-1], c='k', s=4, marker='*', zorder=2)
plt.xlabel('x')
plt.ylabel('y')
plt.grid()
plt.gca().set_aspect('equal', adjustable='box')

plt.tight_layout()
plt.savefig(sys.argv[1]+'/caminho.png', dpi=400)
