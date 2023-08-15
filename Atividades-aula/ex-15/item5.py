import os
import sys
import random
import time

main = 'ising2D.c'
pasta = 'resultados-5'
seed = int(time.time())
L = 100            # Aresta da rede
STEPS = 100500     # Número de MCS
RND = 1           # Condição inicial dos spins
IMG = 0           # Gravar estados
CI  = 0            # Gravar condição inicial
T = [2, 3, 5]              # Temperatura

# Cria a pasta que eu dei o nome
try:
    os.mkdir(pasta)
except FileExistsError:
    os.system(f'rm -rf {pasta}/*')

info = open(f'{pasta}/info.txt', 'w')

# Realiza as amostras
os.system(f'gcc {main} -lm')
#for l in L:
for t in T:
    print(f'Rodando T = {t}')
    start = time.time()
    info.write(f'***Amostra***\n\n')

    
    os.system(f'./a.out {pasta} {seed} {L} {STEPS} {RND} {IMG} {CI} {t}')
    seed += 3

    info.write(f'Seed = {seed}\n')
    info.write(f'L = {L}\n')
    info.write(f'STEPS = {STEPS}\n')
    info.write(f'RND = {RND}\n')
    info.write(f'T = {t}\n')
    info.write(f'Execution time = {time.time() - start:.4f} s\n')
    info.write('-'*35+'\n')
info.close()
