# coding: utf-8

import numpy as np
import matplotlib.pyplot as plt   
from mpl_toolkits.mplot3d import Axes3D

f = open('/home/sunsky/repo/PublicCourse/homework2/sample_data/VelodyneDevice32c/0.txt', 'r')
for i in range(6):
    line = f.readline()

x = []
y = []
z = []

while line:
    line = line.split(',')
    z_tmp = float(line[3])
    if z_tmp < 0:
        line = f.readline()
        continue
    x.append(float(line[1]))
    y.append(float(line[2]))
    z.append(z_tmp)
    line = f.readline()

f.close()
fig=plt.figure(dpi=120)
ax=fig.add_subplot(111,projection='3d')
plt.title('point cloud')
ax.scatter(x,y,z,c='b',marker='.',s=2,linewidth=0,alpha=1,cmap='spectral')

#ax.set_facecolor((0,0,0))
ax.axis('scaled')
# ax.xaxis.set_visible(False)
# ax.yaxis.set_visible(False)
ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')
plt.show()
