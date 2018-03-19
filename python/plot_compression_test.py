import matplotlib.pyplot as plt
import numpy as np
sz = 1502655
data3 = [  (sz- 271382*3)/sz,  (sz- 91315*3)/sz, (sz- 4744*3)/sz, (sz- 1344*3)/sz ,(sz-387*3)/sz,(sz-183*3)/sz, (sz-104*3)/sz, (sz-76*3)/sz ]
data2 = [  0.05, 0.1, 0.5,1,2,3,4,5]
import matplotlib.pyplot as plt

fig = plt.figure()
fig.suptitle('PAA SW Segmentation Compression Ratio', fontsize=14, fontweight='bold')

ax = fig.add_subplot(111)
fig.subplots_adjust(top=0.85)
ax.set_title('Uncompressed size : 1502655 data points')

ax.set_xlabel('% error guarantees')
ax.set_ylabel('compression ratio')

#ax.text(3, 8, 'boxed italics text in data coords', style='italic',
#bbox={'facecolor':'red', 'alpha':0.5, 'pad':10})

#ax.text(2, 6, r'an equation: $E=mc^2$', fontsize=15)

#ax.text(3, 2, u'unicode: Institut f\374r Festk\366rperphysik')

#ax.text(0.95, 0.01, 'colored text in axes coords',
#        verticalalignment='bottom', horizontalalignment='right',
#        transform=ax.transAxes,
#        color='green', fontsize=15)


ax.plot( data2, data3 )
ax.annotate('   271382 segments', xy=(0.005,0.458), xycoords = 'data')
ax.annotate('     91315  segments', xy=(0.01,0.817), xycoords = 'data')

ax.annotate('   4744  segments', xy=(0.05,0.991), xycoords = 'data')
ax.annotate('   1344 segments', xy=(1.0,0.9973), xycoords = 'data')
       
ax.annotate('   387 segments', xy=(2.0,0.9992), xycoords = 'data')
     
ax.annotate(' 183 segments', xy=(3.0,0.9996), xycoords = 'data')
#ax.axis([0, 10, 0, 10])

ax.annotate(' 104 segments', xy=(4.0,0.9997), xycoords = 'data')
ax.annotate(' 76 segments', xy=(5.0,0.9998), xycoords = 'data')
print (data3)

plt.xticks(np.arange(0, 6 , 0.5))
plt.show()




