import matplotlib.pyplot as plt
import sys
import numpy as np

plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})
args = sys.argv[1].split('-')
P = eval(args[1])
L = eval(args[3])

sitio = np.loadtxt(sys.argv[1]+'/track.dat', unpack=True, usecols=0)

caminho = list()
c = list()
for i in range(len(sitio)):
    if sitio[i] == -1:
        caminho.append(c)
        c = list()
    else: c.append(sitio[i])
caminho.append(c)

for c in range(len(caminho)):
    x = np.asarray(list(s%L for s in caminho[c])) + .5
    y = np.asarray(list((L-1) - (s//L) for s in caminho[c])) + .5
    plt.plot(x, y, c='k', linewidth=.4, zorder=2)
    if c == 0:
        plt.scatter(x[0], y[0], c='b', s=4, marker='*', zorder=3)
    if c == len(caminho)-1:
        plt.scatter(x[-1], y[-1], c='r', s=4, marker='*', zorder=3)
plt.xlim(0, L)
plt.ylim(0, L)
plt.vlines((0, L), 0, L, 'k')
plt.hlines((0, L), 0, L, 'k')
plt.grid()
plt.gca().set_aspect('equal', adjustable='box')
plt.axis('off')

plt.tight_layout()
plt.savefig(sys.argv[1]+'/caminho.png', dpi=400)

