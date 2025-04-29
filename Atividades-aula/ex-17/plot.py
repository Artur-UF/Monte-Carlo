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


def chiT(m, N, T):
    m = np.asarray(m)
    n = len(m)
    m2 = sum(m**2)/n
    mm2 = (sum(abs(m))/n)**2
    return N*(m2-mm2)/T


L = [25, 50, 75, 100]           
STEPS = 5000            
RND = 0
IMG = 0                 
CI  = 0                 
TI = 2.
TF = 3.
dT = 0.05
TRANS = 1000 
CR = 0                 


nfiles = 4

ts = list([] for i in range(nfiles))
es = list([] for i in range(nfiles))
ms = list([] for i in range(nfiles))
cts = list([] for i in range(nfiles))
chis = list([] for i in range(nfiles))


f = 0
l = 0
ts[f], es[f], ms[f], cts[f] = np.loadtxt(sys.argv[1]+f'/medidas-L-{L[l]}-TI-1.00-TF-{TF:.2f}-dT-{dT:.2f}-STEPS-{STEPS}-RND-{RND}-TRANS-{TRANS}.dat', unpack=True)
f += 1
for l in range(1, 4):
    ts[f], es[f], ms[f], cts[f] = np.loadtxt(sys.argv[1]+f'/medidas-L-{L[l]}-TI-{TI:.2f}-TF-{TF:.2f}-dT-{dT:.2f}-STEPS-{STEPS}-RND-{RND}-TRANS-{TRANS}.dat', unpack=True)
    f += 1


fig = plt.subplots(1, 2, layout='constrained', figsize=(8, 4))

cores = ['r', 'b', 'g', 'purple']
markers = ['*', '^', 's', 'o']

temp = np.arange(TI, TF+dT, dT)
temp0 = np.arange(1, TF+dT, dT)

chis[0] = list(chiT(ms[0][i*STEPS:(i+1)*STEPS], L[0]**2, temp0[i]) for i in range(len(temp0)))
for j in range(1, nfiles):
    chis[j] = list(chiT(ms[j][i*STEPS:(i+1)*STEPS], L[j]**2, temp[i]) for i in range(len(temp)))

ms[0] = list(sum(abs(ms[0][i*STEPS:(i+1)*STEPS]))/STEPS for i in range(len(temp0)))
for j in range(1, nfiles):
    ms[j] = list(sum(abs(ms[j][i*STEPS:(i+1)*STEPS]))/STEPS for i in range(len(temp)))

# Solução exata para a magnetização 
TC = 2.269185
x = np.linspace(1, TC, 100)
y = lambda x: (1-np.sinh(2/x)**(-4))**(1/8)


plt.subplot(121)
plt.plot(temp0, ms[0], cores[0], markersize=4, marker=markers[0], linewidth=.7, label=f'L={L[0]}', zorder=2)
for i in range(1, nfiles):
    plt.plot(temp, ms[i], cores[i], markersize=4, marker=markers[i], linewidth=.7, label=f'L={L[i]}', zorder=2)
plt.plot(x, y(x), 'k', linewidth=1, label='analytic', zorder=2)
plt.vlines(2.269185, 0, 0.20, color='k', linewidth=1)
plt.xlabel('T')
plt.ylabel(r'$\left \langle \left | m(T) \right | \right \rangle$')
plt.xlim(1, TF)
plt.ylim(0)
plt.legend()
plt.grid()

plt.subplot(122)
plt.plot(temp0, chis[0], cores[0], markersize=4, marker=markers[0], linewidth=.7, label=f'L={L[i]}', zorder=2)
for i in range(1, nfiles):
    plt.plot(temp, chis[i], cores[i], markersize=4, marker=markers[i], linewidth=.7, label=f'L={L[i]}', zorder=2)
plt.vlines(2.269185, -8, 150, color='k', linewidth=1, label=r'$T_{C}$')
plt.xlabel(r'$T$')
plt.ylabel(r'$\chi (T)$')
plt.xlim(TI, TF)
plt.ylim(-8, 150)
plt.legend()
plt.grid()

plt.suptitle(f'{TRANS} until equilibrium '+r'$\mid$'+f' {STEPS} t(MCS) '+r'$\mid \Delta T =$'+f'{dT}')
#plt.show()
plt.savefig(sys.argv[1]+'/plot.png', dpi=400)


