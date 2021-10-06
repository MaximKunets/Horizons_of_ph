import matplotlib.pyplot as plt
import matplotlib.style as style
import pandas as pd
import numpy as np

print("What do you want:\n 0 - CIR\n 1 - LW")
c = int(input())
if c==0:
    data = pd.read_csv('./CIR.txt', sep=r'\s*-\s*', header=0, encoding='utf8', engine='python')
if c==1:
    data = pd.read_csv('./LW.txt', sep=r'\s*_\s*', header=0, encoding='utf8', engine='python')
style.use('ggplot')
x = data['x'].to_numpy()
y = data['U(x,T)'].to_numpy()

plt.ylabel('U(x,T)')
plt.xlabel('x')

plt.plot(x, y)
plt.show()
