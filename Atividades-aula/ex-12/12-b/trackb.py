import matplotlib.pyplot as plt
import sys
import numpy as np

plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})
args = sys.argv[1].split('-')
P = eval(args[1])
L = eval(args[3])

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

sitio = np.loadtxt(sys.argv[1]+'/track.dat', unpack=True)

# AQUI EU CRIO UMA LISTA QUE VAI TER AS LISTAS COM OS CAMINHOS COMPLETOS
caminho = split(sitio, -1)
#--------------------------------------------------

# AQUI EU ITERO SOBRE A LISTA DE CAMINHOS INTEIROS TRANSFORMANDO O NÚMERO DO SÍTIO
# EM X E Y E PLOTO O CAMINHO INTEIRO, ELE TAMBÉ PLOTA UMA ESTRELA AZUL NO INICIO DO
# DO CAMINHO E UMA PRETA NO FIM
for c in range(len(caminho)):
    x = np.asarray(list(s%L for s in caminho[c])) + .5
    y = np.asarray(list((L-1) - (s//L) for s in caminho[c])) + .5
    plt.plot(x, y, c='k', linewidth=.8, zorder=2)
    if c == 0:
        plt.scatter(x[0], y[0], c='g', s=14, marker='*', zorder=3)
    if c == len(caminho)-1:
        plt.scatter(x[-1], y[-1], c='r', s=14, marker='*', zorder=3)
#--------------------------------------------------------------------------
plt.vlines((0, L), 0, L)
plt.xlim(0, L)
plt.ylim(0, L)
plt.vlines((0, L), 0, L, 'k')
plt.hlines((0, L), 0, L, 'k')
plt.gca().set_aspect('equal', adjustable='box')
plt.axis('off')
plt.title(f'{P} passos')

plt.tight_layout()
plt.savefig(sys.argv[1]+'/caminho.png', dpi=400)

