import matplotlib.pyplot as plt
import numpy as np
sz = 1502655
error = 600
data3 = [ (sz- 91597*4)/sz ,(sz-9876*4)/sz,(sz-1157*4)/sz, (sz-410*4)/sz, (sz-125*4)/sz ]
data2 = [0.001* error, 0.01 * error , 0.1 * error, 0.3 * error, error]
data4 = [ (sz- 100318*4)/sz ,(sz-9995*4)/sz,(sz-1159*4)/sz, (sz-410*4)/sz, (sz-125*4)/sz ]

lines3 = plt.plot(data2, data3, label='PAA SW-I Compression')
plt.setp(lines3,color='k',linewidth=2.0)
ines3 = plt.plot(data2, data4, label='PAA SW Compression')
plt.setp(lines3,color='c',linewidth=2.0)

plt.legend()
plt.show()

