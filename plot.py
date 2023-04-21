import numpy as np
import matplotlib.pyplot as plt
from monke.plots import legend

data = np.transpose(np.loadtxt("Data_interpolation.txt"))
x = data[0,:]
interpolation = data[1,:]

data = np.transpose(np.loadtxt("stuetzpunkte.txt"))
stuetz = data[0,:]
y = data[1,:]

def runge(x):
    return 1/(1+x**2)

fig, ax = plt.subplots(figsize = (6, 4.5))
ax.plot(x, runge(x), label = "Runge")
ax.plot(x, interpolation, label="Interpolation", color = "black")
ax.scatter(stuetz, y, label = "Stützpunkte", color = "tab:blue")
legend(ax)
plt.show()