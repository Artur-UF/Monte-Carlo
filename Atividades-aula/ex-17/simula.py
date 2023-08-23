import os
import sys
import random
import time

main = 'ising2D.c'
pasta = 'resultados'
seed = int(time.time())
L = [25, 50, 75, 100]           # Aresta da rede
STEPS = 1000              # Número de MCS
RND = 0                 # Condição inicial dos spins
IMG = 0                 # Gravar estados
CI  = 0                 # Gravar condição inicial
TI = 2.                  # Temperatura Inicial
TF = 4.                  # Temperatura Final
TRANS = 1000           # Final do Transiente 
CR = 0                 # Numero de medidas de Correlação espacial

AM = 1                 # Número de amostras

# Cria a pasta que eu dei o nome
try:
    os.mkdir(pasta)
except FileExistsError:
    os.system(f'rm -rf {pasta}/*')

info = open(f'{pasta}/info.txt', 'w')

# Realiza as amostras
os.system(f'gcc {main} -lm')
print(f"L   STEPS  RND IMG CI TI   TF   TRANS  CR\n")
for l in range(len(L)):
    start = time.time()
    info.write(f'***{AM} Amostra(s)***\n\n')
    info.write(f'Seed = {seed}\n')
    info.write(f'L = {L[l]}\n')
    info.write(f'STEPS = {STEPS}\n')
    info.write(f'RND = {RND}\n')
    info.write(f'IMG = {IMG}\n')
    info.write(f'CI = {CI}\n')
    info.write(f'TI = {TI}\n')
    info.write(f'TF = {TF}\n')
    info.write(f'TRANS = {TRANS}\n')
    info.write(f'CR = {CR}\n')
    
    os.system(f'./a.out {pasta} {seed} {L[l]} {STEPS} {RND} {IMG} {CI} {TI} {TF} {TRANS} {CR}')
    seed += 3
 
    info.write(f'Execution time = {time.time() - start:.4f} s\n')
    info.write('-'*35+'\n')
    print(f'{L[l]:<3d} {STEPS:<6d} {RND:<3d} {IMG:<3d} {CI:<2d} {TI:<.2f} {TF:<.2f} {TRANS:<6d} {CR:<2d}\n')
info.close()

