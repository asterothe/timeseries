import matplotlib.pyplot as plt
import numpy as np
sz = 1502655
data3 = [ (sz- 83386*5)/sz ,(sz-10393*5)/sz,(sz-1209*5)/sz, (sz-431*5)/sz, (sz-137*5)/sz ]
data2 = [1,2,3,4,5]




lines3 = plt.plot(data2, data3, label='PLR Compression')
plt.setp(lines3,color='k',linewidth=2.0)
plt.set_xlabel('xlabel')

plt.legend()
plt.show()

