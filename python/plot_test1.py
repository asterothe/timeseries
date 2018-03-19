import matplotlib.pyplot as plt
import numpy as np
data = np.genfromtxt('../eclipse-workspace/test2/Debug/PAAOut.txt', delimiter=' ')

data2 = np.genfromtxt('../eclipse-workspace/test2/Debug/TSout.txt', delimiter=' ')
plt.xticks(np.arange(1, 1502657, 10000.0))
plt.plot (data)
plt.xlabel('PAA Appoximation')
plt.show()
