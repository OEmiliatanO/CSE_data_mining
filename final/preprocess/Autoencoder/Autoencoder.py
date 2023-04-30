import torch
from torch import nn

class encoder(nn.Module):
    def __init__(self, input_dim, output_dim):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(input_dim, 128)
            nn.Linear(128, 64)
            nn.Linear(64, 32)
            nn.Linear(32, output_dim)
        )
    def forward(self, x):
        return self.net(x)

class decoder(nn.Module):
    def __init__(self, input_dim, output_dim):
        super.__init__()
        self.net = nn.Sequential(
            nn.Linear(input_dim, 32)
            nn.Linear(32, 64)
            nn.Linear(64, 128)
            nn.Linear(128, output_dim)
        )
    def forward(self, x):
        return self.net(x)

class autoencoder(nn.Module):
    def __init__(self, input_dim, output_dim, opt, lr):
        super.__init__()
        self.encoder = encoder(input_dim, output_dim)
        self.decoder = decoder(output_dim, input_dim)
        self.net = nn.Sequential(
            encoder(input_dim, output_dim),
            decoder(output_dim, input_dim)
        )
        self.opt = opt(self.parameters(), lr=lr)
    def forward(self, x):
        return self.net(x)
    def train(self, x, y, loss_fn):
        loss = loss_fn(self.net(x), y)

        self.opt.zero_grad()
        loss.backward()
        self.opt.step()
