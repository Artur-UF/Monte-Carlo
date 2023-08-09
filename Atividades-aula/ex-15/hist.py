import matplotlib.pyplot as plt
import sys
import numpy as np
plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})

t1, e1, m1 = np.loadtxt(sys.argv[1]+'/ising-L-5-T-1-STEPS-5000-rnd-1.dat', unpack=True)
t2, e2, m2 = np.loadtxt(sys.argv[1]+'/ising-L-10-T-1-STEPS-5000-rnd-1.dat', unpack=True)
t3, e3, m3 = np.loadtxt(sys.argv[1]+'/ising-L-50-T-1-STEPS-5000-rnd-1.dat', unpack=True)
t4, e4, m4 = np.loadtxt(sys.argv[1]+'/ising-L-100-T-1-STEPS-5000-rnd-1.dat', unpack=True)

m1 = abs(m1)
m2 = abs(m2)
m3 = abs(m3)
m4 = abs(m4)


fig = plt.subplots(figsize=(8, 4))

nbins=50

corte = 100

plt.subplot(121)
plt.hist(e1[corte:], density=True, histtype='step', label=f'L=5')
plt.hist(e2[corte:], density=True, histtype='step', label=f'L=10')
plt.hist(e3[corte:], density=True, histtype='step', label=f'L=50')
plt.hist(e4[corte:], density=True, histtype='step', label=f'L=100')
plt.xlim(-2.05, -1.85)
plt.legend()
plt.xlabel('E/N')


plt.subplot(122)
plt.hist(m1[corte:], density=True, histtype='step', label=f'L=5')
plt.hist(m2[corte:], density=True, histtype='step', label=f'L=10')
plt.hist(m3[corte:], density=True, histtype='step', label=f'L=50')
plt.hist(m4[corte:], density=True, histtype='step', label=f'L=100')
plt.xlim(0.95, 1.02)
plt.legend()
plt.xlabel(r'$\left |m\right |$')

plt.suptitle('4900 passos no equilíbrio')
plt.tight_layout()
plt.savefig(sys.argv[1]+'/hist.png', dpi=400)
