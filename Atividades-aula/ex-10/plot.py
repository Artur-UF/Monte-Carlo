import matplotlib.pyplot as plt
import numpy as np
import sys
plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 13})
args = sys.argv[1].split('-')
N = eval(args[1])

intg1 = np.loadtxt(sys.argv[1]+'/out1.dat', unpack=True)
intg2 = np.loadtxt(sys.argv[1]+'/out2.dat', unpack=True)

fig = plt.subplots(figsize=(8, 3))

plt.subplot(121)
plt.plot(range(1, N+1), intg1, linewidth=0.5, c='r')
plt.hlines(0.555555, 0, N, 'k')
plt.xlabel('N')
plt.ylabel(r'$I(0.8)$')
plt.ylim(.5, .6)
plt.xlim(0, N)

plt.subplot(122)
plt.plot(range(1, N+1), intg2, linewidth=0.5, c='g')
plt.hlines(5, 0, N, 'k')
plt.ylim(4, 5.2)
plt.xlabel('N')
plt.ylabel(r'$I(-0.8)$')
plt.xlim(0, N)

plt.tight_layout()

plt.savefig(sys.argv[1]+'/plot.png', dpi=400)
