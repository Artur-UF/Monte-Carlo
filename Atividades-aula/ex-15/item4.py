import os
import sys
import random
import time

main = 'ising2D.c'
pasta = 'resultados-4'
seed = int(time.time())
L = 100            # Aresta da rede
STEPS = 110000     # Número de MCS
RND = 0           # Condição inicial dos spins
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
print('Compilou :)')
#for l in L:
start = time.time()
info.write(f'***Amostra***\n\n')
info.write(f'Seed = {seed}\n')
info.write(f'L = {L}\n')
info.write(f'STEPS = {STEPS}\n')
info.write(f'RND = {RND}\n')
info.write(f'Execution time = {time.time() - start:.4f} s\n')
info.write('-'*25+'\n')

os.system(f'./a.out {pasta} {seed} {L} {STEPS} {RND} {IMG} {CI} {T}')
seed += 3

info.close()
print('Rodou tudo :)')

