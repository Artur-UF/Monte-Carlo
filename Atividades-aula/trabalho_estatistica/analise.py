import numpy as np



AM = 1000
NL = 20

t = np.loadtxt(f'rw-AM-{AM}-NL-{NL}.dat', unpack=True)

print(f'Média dos tempos = {sum(t)/AM}')


