import numpy as np
import matplotlib.pyplot as plt
import sys
plt.rcParams.update({"text.usetex" : True, "font.family" : "serif", "font.serif" : ["Computer Modern Serif"], "font.size" : 14})
args = sys.argv[1].split('-')
TA = eval(args[1])
NA = eval(args[3])
LAMB = args[4]

def bintolist(path, n):
	'''
	Função que recebe um path e o número de componentes que tem no array o qual
	está salvo em binário
	'''
	struct_fmt = '=d'
	struct_len = struct.calcsize(struct_fmt)
	struct_unpack = struct.Struct(struct_fmt).unpack_from


	# Lendo e atribuindo os binarios dentro de objetos e listas
	array = list()

	with open(path, "rb") as f:
		for i in range(n):
			data = f.read(struct_len)
			s = struct_unpack(data)
			array.append(float(s[0]))
	return array

#__________________PARA .TXT_________________________________________________
#Nc, crej = np.loadtxt(sys.argv[1]+'/dinamicaC.dat', unpack=True)
#Ns, srej = np.loadtxt(sys.argv[1]+'/dinamicaS.dat', unpack=True)
#____________________________________________________________________________

#__________________PARA .BIN_________________________________________________
#crej = np.load(sys.argv[1]+'/dinamicaC.npy')
srej = np.load(sys.argv[1]+'/dinamicaS.npy')
#____________________________________________________________________________


#piC = crej[TA-1::TA]
piS = srej[TA-1::TA]

#mediaC = sum(piC)/len(piC)
mediaS = sum(piS)/len(piS)

#fig = plt.subplots(figsize=(8, 4))

'''#plt.subplot(121)
plt.hist(piC, bins=50)
plt.vlines(mediaC, 0, 70, 'k', label=f'{mediaC:.3f}')
plt.vlines(np.pi/4, 0, 70, 'r', label=r'$\pi/4$')
#plt.xlim(0, 100)
plt.ylabel(r'\Large{Frequência}')
plt.xlabel(r'$\pi$')
plt.title('Com Rejeição')
plt.legend()
'''
#plt.subplot(122)
plt.hist(piS, bins=50)
plt.vlines(mediaS, 0, 70, 'k', label=f'{mediaS:.3f}')
plt.vlines(np.pi/4, 0, 70, 'r', label=r'$\pi/4$')
#plt.xlim(0.74, 0.82)
plt.xlabel(r'$\pi$')
plt.title('Sem Rejeição')

plt.legend()
plt.tight_layout()
plt.savefig(sys.argv[1]+f'/histograma-final-{LAMB}.png', dpi=400)

