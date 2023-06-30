import matplotlib.pyplot as plt
import numpy as np
import sys
plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})
args = sys.argv[1].split('-')
N = eval(args[1])

intg1 = np.loadtxt(sys.argv[1]+'/out1.dat', unpack=True)
intg2 = np.loadtxt(sys.argv[1]+'/out2.dat', unpack=True)

fig = plt.subplots(figsize=(8, 3))

plt.subplot(121)
plt.hist(intg1, bins=200, density=True)
plt.plot(np.linspace(0, 3, 1000), np.exp(-np.linspace(0, 3, 1000)), 'r')
plt.yscale('log')
plt.xlabel('x')
plt.ylabel(r'$P(x)$')
plt.xlim(0, 3)
plt.title(r'$p(x) = e^{-x}$')

plt.subplot(122)
plt.hist(intg2, bins=200, density=True)
plt.plot(np.linspace(0.0001, 1, 1000), (1-.4)*np.linspace(0.0001, 1, 1000)**(-.4), 'r')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('x')
plt.ylabel(r'$P(x)$')
plt.xlim(0.001, 1)
plt.title(r'$p(x) = (1 - \tau)x^{-\tau}$')

plt.tight_layout()

plt.savefig(sys.argv[1]+'/hist.png', dpi=400)
