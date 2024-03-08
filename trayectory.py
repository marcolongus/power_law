import matplotlib.pyplot as plt
import numpy as np
import random

#from heatmap_rectangle import DIR_PATH

colores = ['blue', 'red', 'green']
#archivo = DIR_PATH + "animacion.txt"
archivo = "data/animacion.txt"

N = 1000
L = 150
np_steps = 90000

delta = 200
x_wave = 20
x_shift = x_wave + 30

animation_step = np.loadtxt(archivo, usecols=2, max_rows=1)

x = np.loadtxt(archivo, usecols=0)
y = np.loadtxt(archivo, usecols=1)

x_r = np.arange(0, L, 5)
y_r = lambda x : (L / delta) * (x - x_shift)
y_perp = lambda x : (-delta / L) * (x - x_shift) + 20


plt.axis('square')
plt.ylim(0, L)
plt.xlim(0, L)

p1 = random.randint(0, N)
p2 = random.randint(0, N)
p3 = random.randint(0, N)
p4 = random.randint(0, N)
print(p1, p2, p3, p4)
s=0.05
plt.scatter(x[p1::N], y[p1::N], s=s)
plt.scatter(x[p2::N], y[p2::N], s=s)
plt.scatter(x[p3::N], y[p3::N], s=s)
plt.scatter(x[p4::N], y[p4::N], s=s)

plt.plot(x_r, y_r(x_r), color='black', linestyle="dashed")
plt.plot(x_r, y_perp(x_r), color='black', linestyle="dashed")
plt.savefig("data/walkers.png")
plt.show()