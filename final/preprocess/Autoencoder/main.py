import sys
import torch
from torch import nn
from Autoencoder import autoencoder
import pandas as pd

batch_size = 16

input_dim = int(sys.argv[1])
output_dim = int(sys.argv[2])
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
encoder = autoencoder(input_dim, output_dim)
encoder.to(device)
rX = pd.read_csv(sys.argv[3]).to_numpy()
rY = pd.read_csv(sys.argv[4]).to_numpy()

X = np.array([rX[i:(i+1)*batch_size] for i in range(len(X)//batch_size)])
Y = np.array([rY[i:(i+1)*batch_size] for i in range(len(Y)//batch_size)])
X = torch.Tensor(X).to(device)
Y = torch.Tensor(Y).to(device)

for i in range(ecoph):
    loss = encoder.train(X[i % len(X)], Y[i % len(Y)], nn.CrossEntropyLoss)
    if _ % 100:
        print(f"loss = {loss}")

X = pd.read_csv(sys.argv[5]).to_numpy()
Y = pd.read_csv(sys.argv[6]).to_numpy()
Z = encoder.encode(X)

Z.to_csv(sys.argv[7])
