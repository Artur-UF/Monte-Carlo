import os
import sys
import random
import time

main = 'ising2D.c'
pasta = 'resultados-3'
seed = int(time.time())
L = [50, 100]            # Aresta da rede
STEPS = 5000     # Número de MCS
RND = [0, 1]           # Condição inicial dos spins
IMG = 0           # Gravar estados
CI  = 0            # Gravar condição inicial
T = 1              # Temperatura

# Cria a pasta que eu dei o nome
try:
    os.mkdir(pasta)
except FileExistsError:
    os.system(f'rm -rf {pasta}/*')

info = open(f'{pasta}/info.txt', 'w')

# Realiza as amostras
os.system(f'gcc {main} -lm')
for l in L:
    for r in RND:
        start = time.time()
        info.write(f'***Amostra 1***\n\n')
        info.write(f'Seed = {seed}\n')
        info.write(f'L = {l}\n')
        info.write(f'STEPS = {STEPS}\n')
        info.write(f'RND = {r}\n')
        info.write(f'Execution time = {time.time() - start:.4f} s\n')

        
        os.system(f'./a.out {pasta} {seed} {l} {STEPS} {r} {IMG} {CI} {T}')
        seed += 3

        info.write('-'*25+'\n')
info.close()
