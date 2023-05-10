import matplotlib.pyplot as plt
import sys
import numpy as np

data_f = open(sys.argv[1])
n = data_f.readline().strip()
n = int(n)

C = []
labelX = {0:[]}
for _ in range(n):
    inp = data_f.readline().strip().split()
    print(inp)
    if int(inp[-1]) in labelX:
        labelX[int(inp[-1])].append([float(x) for x in inp[:2]])
    else:
        labelX[int(inp[-1])] = []
        labelX[int(inp[-1])].append([float(x) for x in inp[:2]])

plt.figure()
color = [np.random.rand(3) for _ in range(len(labelX))]
for j in range(len(labelX)):
    plt.scatter([*map(lambda x: x[0], labelX[j])], [*map(lambda x: x[1], labelX[j])], c = [color[j] for _ in range(len(labelX[j]))])
plt.show()

