import sys
import math
import random
import numpy as np
import pandas as pd
from sklearn.decomposition import PCA
import matplotlib.pyplot as plt

seed = 1
np.random.seed(seed)
random.seed(seed)

n = int(sys.argv[1])
print(f"read_csv:{sys.argv[2]}")
rX = pd.read_csv(sys.argv[2], header = None).to_numpy()
rX = np.nan_to_num(rX, nan = 0, posinf = 999999, neginf = -999999)
print(rX.shape)
print(f"read_csv:{sys.argv[3]}")
rY = pd.read_csv(sys.argv[3], header = None).to_numpy()

pca = PCA(n_components = n)
Z = pca.fit_transform(rX)
print(Z.shape)
print(f"explained variance ratio = {pca.explained_variance_ratio_}")
print(f"explained variance ratio sum = {sum(pca.explained_variance_ratio_)}")

print("save csv", sys.argv[6])
np.savetxt(sys.argv[6], Z, delimiter = ',')

print(f"read_csv:{sys.argv[4]}")
rX = pd.read_csv(sys.argv[4], header = None).to_numpy()
rX = np.nan_to_num(rX, nan = 0, posinf = 999999, neginf = -999999)
print(f"read_csv:{sys.argv[5]}")
rY = pd.read_csv(sys.argv[5], header = None).to_numpy()

Z = pca.transform(rX)

print("save csv", sys.argv[7])
np.savetxt(sys.argv[7], Z, delimiter = ',')
