import sys
import numpy as np
import matplotlib.pyplot as plt

stuetz_data = np.transpose(np.loadtxt(sys.argv[1], skiprows=1))
ergebnis_data = np.transpose(np.loadtxt(sys.argv[2]))

def runge(x):
    return 1/(1+x**2)

plt.subplots(figsize = (6, 4.5))
plt.scatter(stuetz_data[0], stuetz_data[1])
plt.plot(ergebnis_data[0], ergebnis_data[1], label = "Interpolation")
plt.plot(ergebnis_data[0], runge(ergebnis_data[0]), label = "Runge")

plt.legend()
plt.show()