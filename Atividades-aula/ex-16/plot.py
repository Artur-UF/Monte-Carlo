import matplotlib.pyplot as plt
import sys
import numpy as np

plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})
t1, en1, mag1 = np.loadtxt(sys.argv[1]+'/ising-L-100-T-1-STEPS-100500-rnd-1.dat', unpack=True)

fig = plt.subplots(figsize=(8, 4))

corte = 0

plt.subplot(121)
plt.plot(t1[corte:], en1[corte:], linewidth=1, label=fr'$L = 100$')
plt.xlabel('t(MCS)')
plt.ylabel('E/N')
#plt.xscale('log')
plt.grid()
plt.legend()

plt.subplot(122)
plt.plot(t1[corte:], mag1[corte:], linewidth=1, label=r'$L = 100$')
plt.xlabel('t(MCS)')
plt.ylabel('m')
#plt.xscale('log')
plt.grid()
plt.legend()

plt.tight_layout()
plt.show()
plt.savefig(sys.argv[1]+'/plot.png', dpi=400)
