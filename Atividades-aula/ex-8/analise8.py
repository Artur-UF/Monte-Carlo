'''
sudo apt install texlive texlive-latex-extra texlive-fonts-recommended dvipng cm-super
pip install latex
'''
import numpy as np
import matplotlib.pyplot as plt
import sys

plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 14})

N, crej, srej = np.loadtxt(sys.argv[1]+'/dinamica.dat', unpack=True)

args = sys.argv[1].split('-')
TA = eval(args[1])
NA = eval(args[3])

plt.plot(N, crej, 'g', linewidth=.7, label='Com Rejeição')
plt.plot(N, srej, 'r', linewidth=.7, label='Sem Rejeição')
plt.hlines(np.pi/4, 0, TA, 'k', label=r'$\pi/4$')
plt.xlabel(r'$N$')
plt.ylabel(r'$n/N$')
plt.ylim(.77, .83)
plt.xlim(1, TA)
plt.grid()
plt.legend()
plt.title(r'$\lambda$ Fixo')
plt.tight_layout()
plt.savefig(sys.argv[1]+'/simulacao-lambdaFIXO.png', dpi=400)

