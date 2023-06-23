import numpy as np
import matplotlib.pyplot as plt
import sys

plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 14})

N, xrej, yrej, xsrej, ysrej = np.loadtxt(sys.argv[1]+'/tracker.dat', unpack=True)

args = sys.argv[1].split('-')
TA = eval(args[1])
NA = eval(args[3])
LAMB = args[4]

fig = plt.subplots(figsize=(8, 4))

plt.subplot(121)
plt.scatter(xrej, yrej, s=0.2, c='k')
plt.plot(np.linspace(0, 1, 100), np.sqrt(1-np.linspace(0, 1, 100)**2), 'r')
plt.xlim(0, 1)
plt.ylim(0, 1)
plt.title('Com Rejeição')

plt.subplot(122)
plt.scatter(xsrej, ysrej, s=0.2, c='k')
plt.plot(np.linspace(0, 1, 100), np.sqrt(1-np.linspace(0, 1, 100)**2), 'r')
plt.xlim(0, 1)
plt.ylim(0, 1)
plt.title('Sem Rejeição')

#plt.suptitle(r'$\lambda$ Aleatório')
plt.tight_layout()
plt.savefig(sys.argv[1]+'/walk-{LAMB}.png', dpi=400)


