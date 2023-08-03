import matplotlib.pyplot as plt
import sys
import numpy as np

plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})
args = sys.argv[1].split('-')
AM = eval(args[1])

def split(array, flag):
    '''
    Faz a separação de um array numérico de acordo com uma flag numérica
    '''
    arrnd = list()
    a = list()
    for i in range(len(array)):
        if array[i] == flag:
            arrnd.append(a)
            a = list()
        else: a.append(array[i])
    arrnd.append(a)
    return arrnd

sis1 = np.loadtxt(sys.argv[1]+'/50.dat', unpack=True)
sis2 = np.loadtxt(sys.argv[1]+'/100.dat', unpack=True)
sis3 = np.loadtxt(sys.argv[1]+'/150.dat', unpack=True)

rhos = np.arange(.3, .92, 0.01)

sis1 = split(sis1, -1)
sis1 = list(sum(ts)/AM for ts in sis1)
sis1 = list(t for t in sis1)

sis2 = split(sis2, -1)
sis2 = list(sum(ts)/AM for ts in sis2)
sis2 = list(t for t in sis2)

sis3 = split(sis3, -1)
sis3 = list(sum(ts)/AM for ts in sis3)
sis3 = list(t for t in sis3)


plt.plot(rhos[1:], sis1[1:], '-^', markersize=5, linewidth=1, label='L = 50')
plt.plot(rhos, sis2, '-*', markersize=5, linewidth=1, label='L = 100')
plt.plot(rhos, sis3, '-s', markersize=5, linewidth=1, label='L = 150')
plt.ylabel('t')
plt.xlabel(r'$\rho$')
plt.xlim(.3, .9)
plt.ylim(0)
plt.grid()
plt.legend()
plt.title(f'{AM} amostras')

#plt.tight_layout()
plt.savefig(sys.argv[1]+'/plot.png', dpi=400, bbox_inches='tight')

