import matplotlib.pyplot as plt
import sys
import numpy as np

plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})

t1, en1, mag1 = np.loadtxt(sys.argv[1]+'/ising-L-50-T-1-STEPS-5000-rnd-1.dat', unpack=True)
t2, en2, mag2 = np.loadtxt(sys.argv[1]+'/ising-L-100-T-1-STEPS-5000-rnd-1.dat', unpack=True)
upt1, upen1, upmag1 = np.loadtxt(sys.argv[1]+'/ising-L-50-T-1-STEPS-5000-rnd-0.dat', unpack=True)
upt2, upen2, upmag2 = np.loadtxt(sys.argv[1]+'/ising-L-100-T-1-STEPS-5000-rnd-0.dat', unpack=True)

fig = plt.subplots(figsize=(8, 4))

plt.subplot(121)
plt.plot(t1, en1, 'r--', linewidth=1, label=fr'$L = 50 \mid rnd$')
plt.plot(upt1, upen1, 'r', linewidth=1, label=r'$L = 50 \mid s_{i}^{0} = 1$')
plt.plot(t2, en2, 'b--', linewidth=1, label=f'$L = 100 \mid rnd$')
plt.plot(upt2, upen2, 'b', linewidth=1, label=r'$L = 100 \mid  s_{i}^{0} = 1$')
plt.xlabel('t(MCS)')
plt.ylabel('E/N')
plt.xscale('log')
plt.grid()
plt.legend()

plt.subplot(122)
plt.plot(t1, mag1, 'r--', linewidth=1, label=r'$L = 50 \mid rnd$')
plt.plot(upt1, upmag1, 'r', linewidth=1, label=r'$L = 50 \mid s_{i}^{0} = 1$')
plt.plot(t2, mag2, 'b--', linewidth=1, label=r'$L = 100 \mid rnd$')
plt.plot(upt2, upmag2, 'b', linewidth=1, label=r'$L = 100 \mid s_{i}^{0} = 1$')
plt.xlabel('t(MCS)')
plt.ylabel('m')
plt.xscale('log')
plt.grid()
plt.legend()

plt.tight_layout()
plt.savefig(sys.argv[1]+'/plot.png', dpi=400)

