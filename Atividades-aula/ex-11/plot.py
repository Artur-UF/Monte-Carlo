import matplotlib.pyplot as plt
import numpy as np
import sys
plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})
args = sys.argv[1].split('_')
N = eval(args[2])
GAMMA = eval(args[4])
ZETA = eval(args[6])

intg1 = np.loadtxt(sys.argv[1]+'/out1.dat', unpack=True)

plt.plot(range(1, N+1), intg1, linewidth=0.5, c='r', zorder=1)
plt.hlines(5, 0, N, 'k', linestyle='--', linewidth=.8)
plt.ylim(4, 5.2)
plt.xlabel('N')
plt.ylabel(r'$I(-0.8)$')
plt.xlim(0, N)
plt.title(r'$f(x) = x^{\gamma - \zeta}/(1+\zeta)$'+f'\n'+r'$\gamma = $'+f' {GAMMA} '+r'$ \mid \zeta = $'+f' {ZETA}')

plt.tight_layout()

plt.savefig(sys.argv[1]+'/plot.png', dpi=400)
