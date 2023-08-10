import matplotlib.pyplot as plt
import sys
import numpy as np
plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})

t1, e1, m1 = np.loadtxt(sys.argv[1]+'/ising-L-100-T-1-STEPS-100500-rnd-1.dat', unpack=True)

m1 = abs(m1)

fig = plt.subplots(figsize=(8, 4))

corte = 500     # Início do período estacionário
tc = 100        # Tempo de descorrelação

plt.subplot(121)
plt.hist(e1[corte::tc], color='r', density=True, histtype='bar')
plt.xlabel('E/N')


plt.subplot(122)
plt.hist(m1[corte::tc], color='b', density=True, histtype='bar')
plt.xlabel(r'$\left |m\right |$')

plt.suptitle('1000 Independet configurations\nL = 100', y=.95)
plt.tight_layout()
plt.savefig(sys.argv[1]+'/hist.png', dpi=400)
