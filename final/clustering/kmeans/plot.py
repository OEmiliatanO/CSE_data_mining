import matplotlib.pyplot as plt
import sys
import numpy as np

data_f = open(sys.argv[1])
n, m, k = data_f.readline().strip().split()
n, m, k = int(n), int(m), int(k)

labelX = [list() for i in range(k)]
C = []
for _ in range(n):
    inp = data_f.readline().strip().split()
    print(inp)
    labelX[int(inp[-1])].append([float(x) for x in inp[:2]])
for _ in range(m):
    C.append([float(x) for x in data_f.readline().strip().split()])

plt.figure()
color = [np.random.rand(3) for _ in range(k)]
for i, X in enumerate(labelX):
    plt.scatter([*map(lambda x: x[0], X)], [*map(lambda x: x[1], X)], c = [color[i] for _ in range(len(X))])
plt.scatter([*map(lambda x: x[0], C)], [*map(lambda x: x[1], C)], marker='*')
plt.show()

