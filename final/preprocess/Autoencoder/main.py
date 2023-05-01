import sys
import math
import random
import torch
import numpy as np
from torch import nn
from Autoencoder import autoencoder
import pandas as pd
import matplotlib.pyplot as plt

seed = 1
torch.manual_seed(seed)
torch.cuda.manual_seed(seed)
torch.cuda.manual_seed_all(seed)
np.random.seed(seed)
random.seed(seed)
torch.backends.cudnn.benchmark = False
torch.backends.cudnn.deterministic = True

batch_size = 4
epoch = 500

input_dim = int(sys.argv[1])
output_dim = int(sys.argv[2])
device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
print(f"read_csv:{sys.argv[3]}")
rX = pd.read_csv(sys.argv[3]).to_numpy()
rX = np.nan_to_num(rX, nan = 0, posinf = 999999, neginf = -999999)
print(f"read_csv:{sys.argv[4]}")
rY = pd.read_csv(sys.argv[4]).to_numpy()

X = np.array_split(rX, rX.shape[0]//batch_size)
Y = np.array_split(rY, rY.shape[0]//batch_size)
X = np.array(X, dtype = np.float64)
Y = np.array(Y, dtype = np.float64)
X = torch.Tensor(X).to(device)
Y = torch.Tensor(Y).to(device)

encoder = autoencoder(input_dim, output_dim, torch.optim.Adadelta, 0.5)
encoder.to(device)
sigma = 1
loss_fn = nn.MSELoss()
#loss_fn = nn.CrossEntropyLoss()
losses = []
for i in range(epoch):
    x = X[i % len(X)]
    noise = x.new(x.size()).normal_(0, sigma).to(device)
    encoder.zero_grad()
    code, decode = encoder(x+noise)
    loss = loss_fn(x, decode)
    loss.backward()
    encoder.opt.step()
 
    losses.append(loss.detach().cpu().numpy())
    """
    if i % 10 == 0:
        Z, decode = encoder(X)
        print(f"[{i}/{epoch}] loss = {loss_fn(X, decode)}")
    """

plt.plot(losses)
plt.savefig(sys.argv[-1])

X = torch.Tensor(rX).to(device)
Z, decode = encoder(X)
print(f"final loss = {loss_fn(X, decode)}")
Z = Z.detach().cpu().numpy()
print("save csv", sys.argv[7])
np.savetxt(sys.argv[7], Z, delimiter = ',')

rX = pd.read_csv(sys.argv[5]).to_numpy()
rX = np.nan_to_num(rX, nan = 0, posinf = 999999, neginf = -999999)
rY = pd.read_csv(sys.argv[6]).to_numpy()

X = torch.Tensor(rX).to(device)
Z, decode = encoder(X)
print(f"final loss = {loss_fn(X, decode)}")
Z = Z.detach().cpu().numpy()
print("save csv", sys.argv[8])
np.savetxt(sys.argv[8], Z, delimiter = ',')
