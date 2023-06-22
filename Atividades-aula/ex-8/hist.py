import numpy as np
import matplotlib.pyplot as plt
import sys

plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 14})

N, xrej, yrej, xsrej, ysrej = np.loadtxt(sys.argv[1]+'/tracker.dat', unpack=True)


xrej = list(int(xrej[i]/0.01) for i in range(len(xrej)))
yrej = list(int(yrej[i]/0.01) for i in range(len(yrej)))

crej = xrej + yrej

xsrej = list(int(xsrej[i]/0.01) for i in range(len(xsrej)))
ysrej = list(int(ysrej[i]/0.01) for i in range(len(ysrej)))

srej = xsrej + ysrej

fig = plt.subplots(figsize=(8, 4))

plt.subplot(121)
plt.hist(crej, bins=100, range=(0, 100))
plt.xlim(0, 100)
plt.ylabel(r'\Large{Frequência}')
plt.xlabel(r'$x_{i}/0.01$')
plt.title('Com Rejeição')

plt.subplot(122)
plt.hist(srej, bins=100, range=(0, 100))
plt.xlim(0, 100)
plt.xlabel(r'$x_{i}/0.01$')
plt.title('Sem Rejeição')

plt.suptitle(r'$\lambda$ Aleatório')
plt.tight_layout()
plt.savefig(sys.argv[1]+'/histograma-lambdaRAND.png', dpi=400)

