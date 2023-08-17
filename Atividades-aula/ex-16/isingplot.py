import matplotlib.pyplot as plt
import sys
import numpy as np

plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})

L = 100
STEPS = 50000
RND = 1
IMG = 0
CI = 0
T = 3.
TRANS = 1
CR = 0

t, e, m , ct= np.loadtxt(sys.argv[1]+f'/medidas-L-{L}-T-{T:.2f}-STEPS-{STEPS}-RND-{RND}-TRANS-{TRANS}.dat', unpack=True)

fig = plt.subplots(figsize=(8, 4))

corte = 500

plt.subplot(121)
plt.plot(t[:corte], e[:corte], 'r', linewidth=1)
plt.xlabel('t(MCS)')
plt.ylabel('E/N')
#plt.xscale('log')
plt.grid()

plt.subplot(122)
plt.plot(t, m, 'r', linewidth=1)
plt.xlabel('t(MCS)')
plt.ylabel('m')
#plt.xscale('log')
plt.grid()

plt.tight_layout()
plt.savefig(sys.argv[1]+'/isingplot.png', dpi=400)

