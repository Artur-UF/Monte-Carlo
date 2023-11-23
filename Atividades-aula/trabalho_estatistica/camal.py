import random as rd
import time

AM = 1000       # Número de amostras
NL = 20         # Separações do espaço

ark = open(f'rwP-AM-{AM}-NL-{NL}.dat', 'w')

x = 1/3
l = (1-x)/NL
t = 0


start = time.time()
for a in range(AM):
    while x < 1:
        x = x + l if rd.random() > .5 else x - l
        x = x + l if x < 0 else x
        t += 1
    ark.write(f'{t}\n')
    print(f'AM = {a} | t = {t}', end='\r')
    t = 0
    x = 1/3
print(f'Tempo de execução: {time.time()-start:.3f}s')

ark.close()

