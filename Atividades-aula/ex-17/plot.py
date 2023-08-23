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
STEPS = 1000            
RND = 0
IMG = 0                 
CI  = 0                 
TI = 2.
TF = 4.
TRANS = 1000 
CR = 0                 


dT = .05
nfiles = 4

ts = list([] for i in range(nfiles))
es = list([] for i in range(nfiles))
ms = list([] for i in range(nfiles))
cts = list([] for i in range(nfiles))
chis = list([] for i in range(nfiles))


f = 0
for l in range(4):
    ts[f], es[f], ms[f], cts[f] = np.loadtxt(sys.argv[1]+f'/medidas-L-{L[l]}-TI-{TI:.2f}-TF-{TF:.2f}-STEPS-{STEPS}-RND-{RND}-TRANS-{TRANS}.dat', unpack=True)
    f += 1


fig = plt.subplots(layout='constrained', figsize=(8, 4))

cores = ['r', 'b', 'g', 'purple']

temp = np.arange(TI, TF+dT, dT)

for j in range(nfiles):
    chis[j] = list(chiT(ms[j][i*STEPS:(i+1)*STEPS], L[j]**2, temp[i]) for i in range(len(temp)))

for j in range(nfiles):
    ms[j] = list(sum(ms[j][i*STEPS:(i+1)*STEPS])/STEPS for i in range(len(temp)))

plt.subplot(121)
for i in range(nfiles):
    plt.plot(temp, ms[i], cores[i], linestyle='-', linewidth=1, label=f'L={L[i]}')
plt.xlabel('T')
plt.ylabel('m(T)')
plt.xlim(TI, TF)
plt.legend()
plt.grid()

plt.subplot(122)
for i in range(nfiles):
    plt.plot(temp, chis[i], cores[i], linewidth=1, label=f'L={L[i]}')
plt.xlabel(r'$T$')
plt.ylabel(r'$\chi (T)$')
plt.xlim(TI, TF)
plt.legend()
plt.grid()

plt.suptitle(f'{TRANS} until equilibrium '+r'$\mid$'+f' {STEPS} t(MCS) '+r'$\mid \Delta T =$'+f'{dT}')
#plt.show()
plt.savefig(sys.argv[1]+'/plot-unico.png', dpi=400)

