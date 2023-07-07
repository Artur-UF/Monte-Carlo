'''
sudo apt install texlive texlive-latex-extra texlive-fonts-recommended dvipng cm-super
pip install latex
'''
import numpy as np
import matplotlib.pyplot as plt
import sys
import struct
plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 14})
#______EXTRAÇÃO DE ARGUMENTOS________
args = sys.argv[1].split('-')
TA = eval(args[1])
NA = eval(args[3])
LAMB = args[4]
#___________________________________

def bintolist(path, n):
	'''
	Função que recebe um path e o número de componentes que tem no array o qual
	está salvo em binário
	'''
	struct_fmt = '=d'
	struct_len = struct.calcsize(struct_fmt)
	struct_unpack = struct.Struct(struct_fmt).unpack_from


	# Lendo e atribuindo os binarios dentro de objetos e listas
	array = [0]*n

	with open(path, "rb") as f:
		for i in range(n):
			data = f.read(struct_len)
			s = struct_unpack(data)
			array[i] = (float(s[0]))
	return array

# _______________________PARA .TXT_____________________________________
#N, crej, srej = np.loadtxt(sys.argv[1]+'/dinamica.dat', unpack=True)	# Arquivo unico
#Nc, crej = np.loadtxt(sys.argv[1]+'/dinamicaC.dat', unpack=True)		# Arquivos separados
#Ns, srej = np.loadtxt(sys.argv[1]+'/dinamicaS.dat', unpack=True)
#______________________________________________________________________
#________________________PARA .BIN_____________________________________
crej = np.load(sys.argv[1]+'/dinamicaC.npy')
print('Foi 1')
srej = np.load(sys.argv[1]+'/dinamicaS.npy')
print('Foi 2')
#______________ A PARTIR DAQUI TU USA AS LISTAS JÁ PRONTAS_______________________

crej = list(sum(crej[i::TA])/NA for i in range(TA))
srej = list(sum(srej[i::TA])/NA for i in range(TA))


plt.plot(range(1, TA+1), crej, 'g', linewidth=.7, label='Com Rejeição')
plt.plot(range(1, TA+1), srej, 'r', linewidth=.7, label='Sem Rejeição')
plt.hlines(np.pi/4, 0, TA, 'k', label=r'$\pi/4$')
plt.xlabel(r'$N$')
plt.ylabel(r'$n/N$')
plt.ylim(.77, .83)
plt.xlim(1, TA)
plt.grid()
plt.legend()
#plt.title(r'$\lambda$ Fixo')
plt.tight_layout()
plt.savefig(sys.argv[1]+f'/simulacao-{LAMB}.png', dpi=400)

