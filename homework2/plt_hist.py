# coding: utf-8

import numpy as np
import pylab as pl

f = open('/home/sunsky/repo/PublicCourse/homework2/sample_data/VelodyneDevice32c/0.txt', 'r')
for i in range(5):
    line = f.readline()

ranges = []
heights = []

while line:
    line = line.split(',')
    x = float(line[1])
    y = float(line[2])
    z = float(line[3])
    ranges.append(np.sqrt(pow(x,2) + pow(y,2) + pow(z,2)))
    heights.append(z)
    line = f.readline()

f.close()
pl.hist(ranges, bins=15)
pl.xlabel('range')
pl.title('Range Distribution')
pl.savefig('homework2/range_distribution.jpg')
pl.clf()

pl.hist(heights, bins=15)
pl.xlabel('height')
pl.title('Height Distribution')
pl.savefig('homework2/height_distribution.jpg')
