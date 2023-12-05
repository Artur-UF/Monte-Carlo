import numpy as np
import matplotlib.pyplot as plt
plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})

l, ndl, tm =  np.loadtxt(f'rwC_AM_5000_DLI_20_DLF_100_DDL_5.dat', unpack=True)

# Resultado analítico
lmb = lambda n: ((2*n + 1)*np.pi)/2

D = lambda l: (l**2)/2

MFPT = lambda l, n: (2*((-1)**n)*np.cos(lmb(n)/3))/(D(l)*lmb(n)**3)

tau_an = list()
for t in range(len(l)):
    tau = 0
    for n in range(50):
        tau += MFPT(l[t], n)
    tau_an.append(tau)


plt.figure(layout='constrained')
plt.plot(l[::-1], tm[::-1], 'k--', label='Simulation')
plt.scatter(l[::-1], tau_an[::-1], c='r', marker='>', label='Analitic', zorder=3)
plt.legend()
plt.xlabel(r'$l$')
plt.ylabel(r'$\tau$')
plt.grid()
plt.title('Mean First Passage Time (in function of l)')
plt.savefig('compare.png', dpi=400)


