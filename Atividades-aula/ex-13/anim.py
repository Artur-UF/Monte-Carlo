import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import sys
plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})

args = sys.argv[1].split('/')
AM = eval(args[0].split('-')[1])

rho = eval(sys.argv[2])

estados = np.loadtxt(sys.argv[1], unpack=True)


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

estados = split(estados, -1)
estados = np.asarray(estados[:-1])
estados = estados.reshape((len(estados), 150, 150))
print(f'# de frames: {len(estados)}')


def gen():
    global estados, rho
    dt = 1
    ti = 0
    for u0 in estados:
        yield u0, ti, rho
        ti += dt


fig, ax = plt.subplots()
im = plt.imshow(estados[0], origin='lower', cmap='inferno', vmin=0, vmax=3)
plt.xticks([]),plt.yticks([])

def run(data):
    '''
    Roda a animação com os dados fornecidos por 'data'
    '''
    u, ti , rho= data
    im.set_array(u)
    plt.title('Forest Fire\n'+r'$\rho$ = '+f'{rho:.2f}'+r' $\mid$ '+f't = {ti}')


ani = animation.FuncAnimation(fig, run, gen, interval=10, save_count=1500, blit=True)
#plt.show()

# Escolha o formato da animação desejado, gif ou mp4:
#writergif = animation.PillowWriter(fps=30)
#ani.save(path+f'/SH-anim.gif', writer=writergif)

FFwriter = animation.FFMpegWriter(fps=10)
ani.save(args[0]+f'/anim-{rho}-.mp4', writer=FFwriter, dpi=400)

plt.close()
