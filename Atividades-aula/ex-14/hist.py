import matplotlib.pyplot as plt
import sys
import numpy as np

plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})
args = sys.argv[1].split('-')
AM = eval(args[1])

e1, m1 = np.loadtxt(sys.argv[1]+'/ising5.dat', unpack=True)
e2, m2 = np.loadtxt(sys.argv[1]+'/ising10.dat', unpack=True)
e3, m3 = np.loadtxt(sys.argv[1]+'/ising50.dat', unpack=True)
e4, m4 = np.loadtxt(sys.argv[1]+'/ising100.dat', unpack=True)

fig = plt.subplots(figsize=(8, 4))

nbins=50

plt.subplot(121)
plt.hist(e1, histtype='step', label=f'L=5')
plt.hist(e2, histtype='step', label=f'L=10')
plt.hist(e3, histtype='step', label=f'L=50')
plt.hist(e4, histtype='step', label=f'L=100')
plt.legend()
plt.xlabel('E')


plt.subplot(122)
plt.hist(m1, histtype='step', label=f'L=5')
plt.hist(m2, histtype='step', label=f'L=10')
plt.hist(m3, histtype='step', label=f'L=50')
plt.hist(m4, histtype='step', label=f'L=100')
plt.legend()
plt.xlabel('m')

plt.tight_layout()
plt.savefig(sys.argv[1]+'/hist.png', dpi=400)

