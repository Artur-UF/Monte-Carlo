import numpy as np



AM = 100
NL = 20

tC = np.loadtxt(f'rwC-AM-{AM}-NL-{NL}.dat', unpack=True)
tP = np.loadtxt(f'rwP-AM-{AM}-NL-{NL}.dat', unpack=True)


print(f'Média dos tempos C  = {sum(tC)/AM}')
print(f'Média dos tempos PY = {sum(tP)/AM}')

