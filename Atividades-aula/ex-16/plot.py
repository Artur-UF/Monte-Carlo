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
        if array[i] == flag:
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


t1, e1, m1, ct1 = np.loadtxt(sys.argv[1]+'/medidas-L-50-T-1.00-STEPS-10000-RND-1-TRANS-10000.dat', unpack=True)
t2, e2, m2, ct2 = np.loadtxt(sys.argv[1]+'/medidas-L-50-T-2.27-STEPS-10000-RND-1-TRANS-10000.dat', unpack=True)
t3, e3, m3, ct3 = np.loadtxt(sys.argv[1]+'/medidas-L-50-T-3.00-STEPS-10000-RND-1-TRANS-10000.dat', unpack=True)
t4, e4, m4, ct4 = np.loadtxt(sys.argv[1]+'/medidas-L-100-T-1.00-STEPS-10000-RND-1-TRANS-10000.dat', unpack=True)
t5, e5, m5, ct5 = np.loadtxt(sys.argv[1]+'/medidas-L-100-T-2.27-STEPS-10000-RND-1-TRANS-10000.dat', unpack=True)
t6, e6, m6, ct6 = np.loadtxt(sys.argv[1]+'/medidas-L-100-T-3.00-STEPS-10000-RND-1-TRANS-10000.dat', unpack=True)

r1, cr1 = np.loadtxt(sys.argv[1]+'/CR-L-50-T-1.00-STEPS-10000-RND-1-TRANS-10000.dat', unpack=True)
r2, cr2 = np.loadtxt(sys.argv[1]+'/CR-L-50-T-2.27-STEPS-10000-RND-1-TRANS-10000.dat', unpack=True)
r3, cr3 = np.loadtxt(sys.argv[1]+'/CR-L-50-T-3.00-STEPS-10000-RND-1-TRANS-10000.dat', unpack=True)
r4, cr4 = np.loadtxt(sys.argv[1]+'/CR-L-100-T-1.00-STEPS-10000-RND-1-TRANS-10000.dat', unpack=True)
r5, cr5 = np.loadtxt(sys.argv[1]+'/CR-L-100-T-2.27-STEPS-10000-RND-1-TRANS-10000.dat', unpack=True)
r6, cr6 = np.loadtxt(sys.argv[1]+'/CR-L-100-T-3.00-STEPS-10000-RND-1-TRANS-10000.dat', unpack=True)

r1 = split(r1,-1)[0]
r2 = split(r2,-1)[0]
r3 = split(r3,-1)[0]
r4 = split(r4,-1)[0]
r5 = split(r5,-1)[0]
r6 = split(r6,-1)[0]

cr1 = medams(split(cr1,-1))
cr2 = medams(split(cr2,-1))
cr3 = medams(split(cr3,-1))
cr4 = medams(split(cr4,-1))
cr5 = medams(split(cr5,-1))
cr6 = medams(split(cr6,-1))

fig = plt.subplots(figsize=(10, 8))

plt.subplot(221)
plt.plot(t1, ct1, 'r--', linewidth=1, zorder=3)
plt.plot(t2, ct2, 'g--', linewidth=1, zorder=2)
plt.plot(t3, ct3, 'b--', linewidth=1, zorder=1)
plt.xlabel('t(MCS)')
plt.ylabel('C(t)')
plt.title(r'$L = 50$')
plt.grid()

plt.subplot(222)
plt.plot(t4, ct4, 'r', linewidth=1, zorder=3, label=fr'$T = 1$')
plt.plot(t5, ct5, 'g', linewidth=1, zorder=2, label=fr'$T = 2.27$')
plt.plot(t6, ct6, 'b', linewidth=1, zorder=1, label=fr'$T = 3$')
plt.xlabel('t(MCS)')
plt.ylabel('C(t)')
plt.title(r'$L = 100$')
plt.ylim(-0.07777777, 0.1)
plt.grid()
plt.legend()

plt.subplot(223)
plt.plot(r1, cr1, 'r--', linewidth=1)
plt.plot(r2, cr2, 'g--', linewidth=1)
plt.plot(r3, cr3, 'b--', linewidth=1)
plt.xlabel('r')
plt.ylabel('C(r)')
plt.grid()

plt.subplot(224)
plt.plot(r4, cr4, 'r', linewidth=1)
plt.plot(r5, cr5, 'g', linewidth=1)
plt.plot(r6, cr6, 'b', linewidth=1)
plt.xlabel('r')
plt.ylabel('C(r)')
plt.grid()

plt.tight_layout()
#plt.show()
plt.savefig(sys.argv[1]+'/plot.png', dpi=400)


