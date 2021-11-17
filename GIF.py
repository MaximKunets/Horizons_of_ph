import numpy as np
import random as rnd
import pandas as pd
import matplotlib.style as style
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from celluloid import Camera

#data = pd.read_csv('./TVD.txt', sep=r'\s*_\s*', header=0, encoding='utf8', engine='python')
#style.use('ggplot')
#x = data['x'].to_numpy()
#y = data['F(x)'].to_numpy()

x_max = []
y = []

f = open('TVD.txt', 'r')
for line in f:
    line = line.strip()
    y.append(float(line.split(' ')[0]))
    x_max.append(float(line.split(' ')[1]))
x_max = np.asarray(x_max).reshape(250, 500)
# for i in range(0, 500):
#     x.append(x_max[0][i])
y = np.asarray(y).reshape(250, 500)

pl = plt.figure()
camera = Camera(pl)
plt.xlabel('x')
plt.ylabel('F(x)')
# plt.plot(x_max[0], y[0], color='red')
# plt.show()
for i in range(0, 250, 5):
    plt.plot(x_max[0][:500], y[i], color='red')
    plt.pause(0.05)
    camera.snap()
animation = camera.animate()
animation.save('animation.gif', writer='Pillow', fps=10)