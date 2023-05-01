import sys
import math
import torch
import numpy as np
from torch import nn
from Autoencoder import autoencoder
import pandas as pd

batch_size = 16

input_dim = int(sys.argv[1])
output_dim = int(sys.argv[2])
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
encoder = autoencoder(input_dim, output_dim, torch.optim.Adadelta, 1)
encoder.to(device)
print(f"read_csv:{sys.argv[3]}")
rX = pd.read_csv(sys.argv[3]).to_numpy()
print(f"read_csv:{sys.argv[4]}")
rY = pd.read_csv(sys.argv[4]).to_numpy()

print(rX.shape)
print(rY.shape)
X = np.array_split(rX, len(rX)//batch_size)
X = np.array(X)
print(X[-1].shape)
Y = np.ndarray(np.array_split(rY, batch_size), dtype=np.float64)
print(X.shape)
print(Y.shape)
X = torch.Tensor(X).to(device)
Y = torch.Tensor(Y).to(device)

for i in range(ecoph):
    loss = encoder.train(X[i % len(X)], Y[i % len(Y)], nn.CrossEntropyLoss)
    if _ % 100:
        print(f"loss = {loss}")

Z = encoder.encode(X).detach().cpu().numpy()
np.savetxt(sys.argv[7], Z, delimiter = ',')

X = pd.read_csv(sys.argv[5]).to_numpy()
Y = pd.read_csv(sys.argv[6]).to_numpy()

Z = encoder.encode(X).detach().cpu().numpy()
np.savetxt(sys.argv[8], Z, delimiter = ',')
