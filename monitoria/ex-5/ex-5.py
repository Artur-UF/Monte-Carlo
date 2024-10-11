import numpy as np
import glob
import matplotlib.pyplot as plt

path = 'datasaurusdozen'

arks = glob.glob(path+'/data*')

x = []
y = []

for i in range(len(arks)):
    xi, yi = np.loadtxt(arks[i], unpack=True)
    x.append(xi)
    y.append(yi)

n = len(x[0])

fig, ax = plt.subplots(1, 1, figsize=(10, 10), layout='constrained')

for i in range(len(arks)):
    xm = sum(x[i])/n
    ym = sum(y[i])/n
    x2m = sum(x[i]**2)/n
    y2m = sum(y[i]**2)/n
    sigmax = x2m - xm**2
    sigmay = y2m - ym**2

    plt.scatter(x[i], y[i], label=f'x = {xm:.2f}+-{sigmax:.2f}, y = {ym:.2f}+-{sigmay:.2f})')
    plt.scatter(xm, ym, marker='+', s=100)
plt.legend()
plt.savefig('saurus.png', dpi=400)

