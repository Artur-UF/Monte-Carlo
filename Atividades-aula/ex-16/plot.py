import matplotlib.pyplot as plt
import sys
import numpy as np
plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})

def split(array, flag):
    '''
    Faz a separação de um array numérico de acordo com uma flag numérica
    '''
    arrnd = list()
    a = list()
    for i in range(len(array)):
        if array[i] == flag and type(flag) == int:
            arrnd.append(a)
            a = list()
        else: a.append(array[i])
    arrnd.append(a)
    return arrnd[:-1]

def medams(ams):
    '''
    Recebe um array de amostras e faz e retorna um array com a media de todas
    '''
    nam = len(ams)
    n = len(ams[0])
    med = np.zeros(n)
    for i in range(nam):
        for j in range(n):
            med[j] += ams[i][j]
    return med/nam

L = [50, 100]           
STEPS = 10000            
RND = 1                 
IMG = 0                 
CI  = 0                 
T = [2.27, 2.3, 2.35, 3.]
TRANS = [5000, 15000]            
CR = 10                 

ts = list([] for i in range(8))
es = list([] for i in range(8))
ms = list([] for i in range(8))
cts = list([] for i in range(8))
rs = list([] for i in range(8))
crs = list([] for i in range(8))


f = 0
for l in range(2):
    for t in range(4):
        ts[f], es[f], ms[f], cts[f] = np.loadtxt(sys.argv[1]+f'/medidas-L-{L[l]}-T-{T[t]:.2f}-STEPS-10000-RND-1-TRANS-{TRANS[l]}.dat', unpack=True)
        f += 1
f = 0
for l in range(2):
    for t in range(4):
        rs[f], crs[f] = np.loadtxt(sys.argv[1]+f'/CR-L-{L[l]}-T-{T[t]:.2f}-STEPS-10000-RND-1-TRANS-{TRANS[l]}.dat', unpack=True)
        f += 1

for i in range(8):
    ts[i] = split(ts[i],-1)[0]

for i in range(8):
    rs[i] = split(rs[i],-1)[0]

for i in range(8):
    cts[i] = medams(split(cts[i],-1))

for i in range(8):
    crs[i] = medams(split(crs[i],-1))

mosaic = """AABB;.CC."""

fig = plt.figure(layout='constrained', figsize=(13, 8))
axs = fig.subplot_mosaic(mosaic)

cores = ['r', 'g', 'b', 'purple']

y = lambda r: r**(-1/4)
r = np.linspace(1, 100)
escala = 1.5

for i in range(4):
    axs['A'].plot(ts[i], cts[i], cores[i], linewidth=1)
axs['A'].set(xlabel='t(MCS)', ylabel='C(t)', title=r'$L = 50$', xscale='log', yscale='log', xlim=(1, 100), ylim=(0.01, 1))
axs['A'].plot(r, y(r)/escala, 'k', label=r'$r^{-1/4}$')
axs['A'].grid()

for i in range(4, 8):
    axs['B'].plot(ts[i], cts[i], cores[i-4], linewidth=1, label=f'T = {T[i-4]}')
axs['B'].set(xlabel='t(MCS)', ylabel='C(t)', title=r'$L = 100$', xscale='log', yscale='log', xlim=(1, 100), ylim=(0.01, 1))
axs['B'].plot(r, y(r)/escala, 'k', label=r'$r^{-1/4}$')
axs['B'].grid()
axs['B'].legend()

y = lambda r: r**(-1/4)
r = np.linspace(1, 10)

for i in range(4):
    axs['C'].plot(rs[i], crs[i], color=cores[i], linestyle='--', linewidth=1)
for i in range(4, 8):
    axs['C'].plot(rs[i], crs[i], cores[i-4], linewidth=1)
#axs['C'].plot([], [], label='-- L = 50\n| L=100')
axs['C'].plot(r, y(r), 'k', label=r'$r^{-1/4}$')
axs['C'].set(xlabel='r', ylabel='C(r)', xlim=(1, 10), ylim=(.01, 1), xscale='log', yscale='log')
axs['C'].grid()
axs['C'].legend(title='- - L=50\n --- L=100')

#plt.show()
plt.savefig(sys.argv[1]+'/plot-logCt.png', dpi=400)


