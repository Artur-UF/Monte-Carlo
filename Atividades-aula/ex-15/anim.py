import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import sys
plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 12})

args = sys.argv[1].split('/')

L = eval(args[1].split('-')[1])
RND = eval(args[1].split('-')[3][0])

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

estados = split(estados, -2)
estados = np.asarray(estados[:-1])
estados = estados.reshape((len(estados), L, L))
print(f'# de frames: {len(estados)}\n')


def gen():
    global estados
    dt = 1
    ti = 0
    for u0 in estados:
        yield u0, ti
        ti += dt


fig, ax = plt.subplots()
im = plt.imshow(estados[0], origin='lower', cmap='inferno', vmin=0, vmax=3)
plt.xticks([]),plt.yticks([])

def run(data):
    '''
    Roda a animação com os dados fornecidos por 'data'
    '''
    u, ti = data
    print(f'\rt = {ti}', end='')
    im.set_array(u)
    plt.title(f'Ising\nt = {ti}')


# save_count = qunatos frames ele salva
ani = animation.FuncAnimation(fig, run, gen, interval=10, save_count=1500, blit=True)
#plt.show()

# Escolha o formato da animação desejado, gif ou mp4:
#writergif = animation.PillowWriter(fps=30)
#ani.save(path+f'/SH-anim.gif', writer=writergif)

FFwriter = animation.FFMpegWriter(fps=30)
ani.save(args[0]+f'/anim-L-{L}-rnd-{RND}.mp4', writer=FFwriter, dpi=400)

plt.close()
