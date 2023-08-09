import matplotlib.pyplot as plt
import sys
import numpy as np

plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})

t1, en1, mag1 = np.loadtxt(sys.argv[1]+'/ising-L-5-T-1-STEPS-5000-rnd-1.dat', unpack=True)
t2, en2, mag2 = np.loadtxt(sys.argv[1]+'/ising-L-10-T-1-STEPS-5000-rnd-1.dat', unpack=True)
t3, en3, mag3 = np.loadtxt(sys.argv[1]+'/ising-L-50-T-1-STEPS-5000-rnd-1.dat', unpack=True)
t4, en4, mag4 = np.loadtxt(sys.argv[1]+'/ising-L-100-T-1-STEPS-5000-rnd-1.dat', unpack=True)

fig = plt.subplots(figsize=(8, 4))

corte = 100

plt.subplot(121)
plt.plot(t1[corte:], en1[corte:], linewidth=1, label=fr'$L = 5 $')
plt.plot(t2[corte:], en2[corte:], linewidth=1, label=r'$L = 10$')
plt.plot(t3[corte:], en3[corte:], linewidth=1, label=f'$L = 50$')
plt.plot(t4[corte:], en4[corte:], linewidth=1, label=r'$L = 100$')
plt.xlabel('t(MCS)')
plt.ylabel('E/N')
#plt.xscale('log')
plt.grid()
plt.legend()

plt.subplot(122)
plt.plot(t1[corte:], mag1[corte:], linewidth=1, label=r'$L = 5$')
plt.plot(t2[corte:], mag2[corte:], linewidth=1, label=r'$L = 10$')
plt.plot(t3[corte:], mag3[corte:], linewidth=1, label=r'$L = 50$')
plt.plot(t4[corte:], mag4[corte:], linewidth=1, label=r'$L = 100$')
plt.xlabel('t(MCS)')
plt.ylabel('m')
#plt.xscale('log')
plt.grid()
plt.legend()

plt.tight_layout()
plt.savefig(sys.argv[1]+'/plot.png', dpi=400)

