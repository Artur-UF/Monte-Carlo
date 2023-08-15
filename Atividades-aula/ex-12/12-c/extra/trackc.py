import matplotlib.pyplot as plt
import sys
import numpy as np

plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})
args = sys.argv[1].split('-')
P = eval(args[1])
L = eval(args[3])
AM = eval(args[7])

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

simul = np.loadtxt(sys.argv[1]+'/track.dat', unpack=True, usecols=0)
msd = np.loadtxt(sys.argv[1]+'/msd.dat', unpack=True, usecols=0)

amostras = split(simul, -2)

# PREPARO A MAIOR AMOSTRA PRA PLOTAR
amplot = max(amostras, key=lambda k: len(k))    # retorna a maior lista dentro da lista amostras
caminho = split(amplot, -1)

fig = plt.subplots(figsize=(8, 4))
plt.subplot(121)
for c in range(len(caminho)):
    x = np.asarray(list(s%L for s in caminho[c])) + .5
    y = np.asarray(list((L-1) - (s//L) for s in caminho[c])) + .5
    plt.plot(x, y, c='k', linewidth=.8, zorder=2)
    if c == 0:
        plt.scatter(x[0], y[0], c='g', s=4, marker='*', zorder=3)
    if c == len(caminho)-1:
        plt.scatter(x[-1], y[-1], c='r', s=4, marker='*', zorder=3)
plt.xlim(0, L)
plt.ylim(0, L)
plt.vlines((0, L), 0, L, 'k')
plt.hlines((0, L), 0, L, 'k')
plt.gca().set_aspect('equal', adjustable='box')
plt.axis('off')
plt.title(f'Maior amostra\n{len(amplot)} passos')

#___________________MSD_________________________
msds = split(msd, -2)

media = np.zeros(len(max(msds, key=lambda k: len(k))))
n = 0
for i in range(len(max(msds, key=lambda k: len(k)))):
    for j in range(len(msds)):
        if i < len(msds[j])-1:
            media[i] += msds[j][i]
            n += 1
    if n > 0: media[i] /= n
    n = 0

#_______________NORMAL___________________
x = np.linspace(len(media)/6, len(media)/2)
y = (x/5)**1.5
xmed = range(len(media))

plt.subplot(122)
'''for i in range(len(msds)):
    xi = range(len(msds[i]))
    yi = msds[i]
    plt.plot(xi, yi, linewidth=.3)'''
plt.plot(xmed[:-1], media[:-1], c='k', linewidth=1, label='MSD')
plt.plot(x, y, c='r', linewidth=1, linestyle='--', label=r'$t^{3/2}$')
plt.ylabel('MSD')
plt.xscale('log')
plt.yscale('log')
plt.xlabel('N')
plt.title(f'MSD: {AM} amostras')
plt.legend()

plt.tight_layout()
plt.savefig(sys.argv[1]+'/caminho.png', dpi=400)


