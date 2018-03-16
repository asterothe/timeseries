import matplotlib.pyplot as plt
import numpy as np
data = np.genfromtxt('../eclipse-workspace/test2/Debug/PLROut.txt', delimiter=' ')

data2 = np.genfromtxt('../eclipse-workspace/test2/Debug/TSout.txt', delimiter=' ')
# plt.xticks(np.arange(1, 1502657, 10000.0))
plt.plot (data2)
plt.ylabel('some numbers')
plt.show()
