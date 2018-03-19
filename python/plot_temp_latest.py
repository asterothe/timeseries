import matplotlib.pyplot as plt
import numpy as np
data = np.genfromtxt('../eclipse-workspace/test2/Debug/PAAout_FL.txt', delimiter=' ')

data2 = np.genfromtxt('../eclipse-workspace/test2/Debug/TSout.txt', delimiter=' ')
data3 = np.genfromtxt('../eclipse-workspace/test2/Debug/PAAout_SWI.txt', delimiter=' ')
data4 = np.genfromtxt('../eclipse-workspace/test2/Debug/PAAout_SW.txt', delimiter=' ')
plt.xticks(np.arange(1, 2086832, 100000.0))
#plt.subplot(211)
lines2 = plt.plot (data,label='PAA FL')
plt.setp(lines2, color = 'r', linewidth=2.0)
plt.xlabel('PLR Segmentation')
#plt.subplot(212)
lines = plt.plot(data2,label='Original TS')
plt.setp(lines, color='k', linewidth=0.3)
#plt.title('Easy as 1, 2, 3') # subplot 211 title
lines4 = plt.plot(data4,label='PAA SW')
plt.setp(lines4,color ='b' ,linewidth=2.0)
lines3 = plt.plot(data3,label='PAA SW-I')
plt.setp(lines3,color='k',linewidth=1.5,linestyle=':')


plt.legend()
plt.show()

