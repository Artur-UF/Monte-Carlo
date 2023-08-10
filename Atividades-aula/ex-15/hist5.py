import matplotlib.pyplot as plt
import sys
import numpy as np
plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})

t1, e1, m1 = np.loadtxt(sys.argv[1]+'/ising-L-100-T-1-STEPS-100500-rnd-1.dat', unpack=True)
t2, e2, m2 = np.loadtxt(sys.argv[1]+'/ising-L-100-T-2-STEPS-100500-rnd-1.dat', unpack=True)
t3, e3, m3 = np.loadtxt(sys.argv[1]+'/ising-L-100-T-3-STEPS-100500-rnd-1.dat', unpack=True)
t4, e4, m4 = np.loadtxt(sys.argv[1]+'/ising-L-100-T-5-STEPS-100500-rnd-1.dat', unpack=True)

m1 = abs(m1)
m2 = abs(m2)
m3 = abs(m3)
m4 = abs(m4)

fig = plt.subplots(figsize=(8, 4))

corte = 500     # Início do período estacionário
tc = 100        # Tempo de descorrelação

plt.subplot(121)
plt.hist(e1[corte::tc], density=True, histtype='step', label=f'T=1')
plt.hist(e2[corte::tc], density=True, histtype='step', label=f'T=2')
plt.hist(e3[corte::tc], density=True, histtype='step', label=f'T=3')
plt.hist(e4[corte::tc], density=True, histtype='step', label=f'T=5')
plt.legend()
plt.xlabel('E/N')


plt.subplot(122)
plt.hist(m1[corte::tc], density=True, histtype='step', label=f'T=1')
plt.hist(m2[corte::tc], density=True, histtype='step', label=f'T=2')
plt.hist(m3[corte::tc], density=True, histtype='step', label=f'T=3')
plt.hist(m4[corte::tc], density=True, histtype='step', label=f'T=5')
plt.legend()
plt.xlabel(r'$\left |m\right |$')

plt.suptitle('1000 Independet configurations\nL = 100', y=.95)
plt.tight_layout()
plt.savefig(sys.argv[1]+'/hist.png', dpi=400)
