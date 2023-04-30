import matplotlib.pyplot as plt
import numpy as np
import sys

f = open(sys.argv[1])

acc = []
try:
    while True:
        s = f.readline()
        acc.append(float(s.split(' ')[1]))
except:
    pass

n = [i for i in range(1,102)]
#print(acc)
#print(n)
assert len(n) == len(acc), "length isn't correct"
plt.figure()
plt.xlabel('k')
plt.ylabel('acc')
plt.plot(n, acc)
plt.show()
