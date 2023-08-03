import matplotlib.pyplot as plt
import sys
import numpy as np

plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})
args = sys.argv[1].split('-')
MCSSIZE = eval(args[1])
STEPS = eval(args[3])

t1, en1, mag1 = np.loadtxt(sys.argv[1]+'/ising50.dat', unpack=True)
t2, en2, mag2 = np.loadtxt(sys.argv[1]+'/ising100.dat', unpack=True)
upt1, upen1, upmag1 = np.loadtxt(sys.argv[1]+'/upising50.dat', unpack=True)
upt2, upen2, upmag2 = np.loadtxt(sys.argv[1]+'/upising100.dat', unpack=True)

tt = 6000

fig = plt.subplots(figsize=(10, 8))

plt.subplot(221)
#plt.plot(t1, en1, linewidth=1, label=f'RAND')
plt.plot(upt1, upen1, linewidth=1, label=r'$s_{0} = 1$')
plt.xlabel('t(MCS)')
plt.ylabel('E/N')
plt.grid()
plt.legend()
plt.title('L = 50')

plt.subplot(222)
#plt.plot(t2, en2, linewidth=1, label=f'RAND')
plt.plot(upt2, upen2, linewidth=1, label=r'$s_{0} = 1$')
plt.xlabel('t(MCS)')
plt.ylabel('E/N')
plt.grid()
plt.legend()
plt.title('L = 100')

plt.subplot(223)
#plt.plot(t1, mag1, linewidth=1, label=f'RAND')
plt.plot(upt1, upmag1, linewidth=1, label=r'$s_{0} = 1$')
plt.xlabel('t(MCS)')
plt.ylabel('m')
plt.grid()
plt.legend()

plt.subplot(224)
#plt.plot(t2, mag2, linewidth=1, label=f'RAND')
plt.plot(upt2, upmag2, linewidth=1, label=r'$s_{0} = 1$')
plt.xlabel('t(MCS)')
plt.ylabel('m')
plt.grid()
plt.legend()

plt.tight_layout()
plt.savefig(sys.argv[1]+'/plotup.png', dpi=400)

