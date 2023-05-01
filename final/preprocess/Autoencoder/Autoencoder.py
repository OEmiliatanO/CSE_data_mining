import torch
from torch import nn

class encoder(nn.Module):
    def __init__(self, input_dim, output_dim):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(input_dim, 512),
            nn.ReLU(),
            nn.Linear(512, 256),
            nn.ReLU(),
            nn.Linear(256, 128),
            nn.ReLU(),
            nn.Linear(128, 64),
            nn.ReLU(),
            nn.Linear(64, output_dim)
        )
        self.flatten = nn.Flatten()
    def forward(self, x):
        return self.net(x)

class decoder(nn.Module):
    def __init__(self, input_dim, output_dim):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(input_dim, 64),
            nn.ReLU(),
            nn.Linear(64, 128),
            nn.ReLU(),
            nn.Linear(128, 256),
            nn.ReLU(),
            nn.Linear(256, 512),
            nn.ReLU(),
            nn.Linear(512, output_dim),
        )
        self.flatten = nn.Flatten()
    def forward(self, x):
        return self.net(x)

class autoencoder(nn.Module):
    def __init__(self, input_dim, output_dim, opt, lr):
        super().__init__()
        self.encoder = encoder(input_dim, output_dim)
        self.decoder = decoder(output_dim, input_dim)
        self.opt = opt(self.parameters(), lr=lr)
        self.flatten = nn.Flatten()
    
    def forward(self, x):
        code = self.encoder(x)
        decode = self.decoder(code)
        return code, decode

   
    def encode(self, x):
        return self.encoder(x)
