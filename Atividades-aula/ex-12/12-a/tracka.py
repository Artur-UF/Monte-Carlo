import matplotlib.pyplot as plt
import sys
import numpy as np
plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})
args = sys.argv[1].split('-')
N = eval(args[1])
AM = eval(args[3])
STEP = eval(args[5])

x, y = np.loadtxt(sys.argv[1]+'/track.dat', unpack=True)
n, msd = np.loadtxt(sys.argv[1]+'/msd.dat', unpack=True)

fig = plt.subplots(figsize=(8, 4))


plt.subplot(121)
plt.plot(x, y, c='k', linewidth=.4)
plt.scatter(x[0], y[0], c='g', s=4, marker='*', zorder=2)
plt.scatter(x[-1], y[-1], c='r', s=4, marker='*', zorder=2)
plt.axis('off')
plt.vlines((min(x), max(x)), min(y), max(y), 'k', linewidth=1)
plt.hlines((min(y), max(y)), min(x), max(x), 'k', linewidth=1)
plt.gca().set_aspect('equal', adjustable='box')
plt.title('1ª Amostra')

x = range(int(3*N/4))

plt.subplot(122)
plt.plot(n, msd, c='r', linewidth=.5, zorder=3)
plt.plot(x, x, c='k', linestyle='--', linewidth=.8)
plt.xlabel('N')
plt.ylabel('MSD')
plt.title(f'MSD: {AM} amostras')
plt.xlim(0, N)
plt.ylim(min(msd), max(msd))
plt.grid()

plt.tight_layout()
plt.savefig(sys.argv[1]+'/plots.png', dpi=400)

