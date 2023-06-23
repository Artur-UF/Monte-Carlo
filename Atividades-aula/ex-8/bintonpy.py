'''
Esse script vai transformar um arquivo .bin em .npy

primeiro argumento é o patho do .bin e o segundo é o path do .npy
'''
import numpy as np
import sys
import struct
args = sys.argv[1].split('-')
TA = eval(args[1])
NA = eval(args[3])
def bintolist(path, n):
	struct_fmt = '=d'
	struct_len = struct.calcsize(struct_fmt)
	struct_unpack = struct.Struct(struct_fmt).unpack_from


	# Lendo e atribuindo os binarios dentro de objetos e listas
	array = np.zeros(n)

	with open(path, "rb") as f:
		for i in range(n):
			data = f.read(struct_len)
			s = struct_unpack(data)
			array[i] = (float(s[0]))
	return array

np.save(sys.argv[2], bintolist(sys.argv[1], TA*NA))

