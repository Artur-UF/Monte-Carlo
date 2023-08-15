# PQ NÃO TA ESCREVENDO UNS CR????? TA CERTO O CR???
import os
import sys
import random
import time

main = 'ising2D.c'
pasta = 'resultados'
seed = int(time.time())
L = [50, 100]           # Aresta da rede
STEPS = 10000              # Número de MCS
RND = 1                 # Condição inicial dos spins
IMG = 0                 # Gravar estados
CI  = 0                 # Gravar condição inicial
T = [1., 2.27, 3.]      # Temperatura
TRANS = 10000           # Final do Transiente 
CR = 10                 # Numero de medidas de Correlação espacial

# Cria a pasta que eu dei o nome
try:
    os.mkdir(pasta)
except FileExistsError:
    os.system(f'rm -rf {pasta}/*')

info = open(f'{pasta}/info.txt', 'w')

# Realiza as amostras
os.system(f'gcc {main} -lm')
print(f"L   STEPS  RND IMG CI T    TRANS  CR\n")
for l in L:
    for t in T:
        start = time.time()
        info.write(f'***Amostra***\n\n')
        info.write(f'Seed = {seed}\n')
        info.write(f'L = {l}\n')
        info.write(f'STEPS = {STEPS}\n')
        info.write(f'RND = {RND}\n')
        info.write(f'T = {t}\n')
        
        os.system(f'./a.out {pasta} {seed} {l} {STEPS} {RND} {IMG} {CI} {t} {TRANS} {CR}')
        seed += 3
    
        info.write(f'Execution time = {time.time() - start:.4f} s\n')
        info.write('-'*35+'\n')
        print(f'{l:<3d} {STEPS:<6d} {RND:<3d} {IMG:<3d} {CI:<2d} {t:<.2f} {TRANS:<6d} {CR:<2d}\n')
info.close()

