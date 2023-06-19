import numpy as np
import matplotlib.pyplot as plt
import sys

N, xrej, yrej, xsrej, ysrej = np.loadtxt(sys.argv[1]+'/tracker.dat', unpack=True)


xrej = list(int(xrej[i]/0.01) for i in range(len(xrej)))
yrej = list(int(yrej[i]/0.01) for i in range(len(yrej)))
xsrej = list(int(xsrej[i]/0.01) for i in range(len(xsrej)))
ysrej = list(int(ysrej[i]/0.01) for i in range(len(ysrej)))

fig = plt.subplots(figsize=(8, 8))

plt.subplot(221)
plt.hist(xrej, bins=100, range=(0, 100))
plt.xlim(0, 100)
plt.title('Com Rejeição')

plt.subplot(222)
plt.hist(xsrej, bins=100, range=(0, 100))
plt.xlim(0, 100)
plt.title('Sem Rejeição')

plt.subplot(223)
plt.hist(yrej, bins=100, range=(0, 100))
plt.xlim(0, 100)

plt.subplot(224)
plt.hist(ysrej, bins=100, range=(0, 100))
plt.xlim(0, 100)


plt.tight_layout()
plt.savefig(sys.argv[1]+'/histograma.png', dpi=200)

