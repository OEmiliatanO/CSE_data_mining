import torch
from torch import nn

class encoder(nn.Module):
    def __init__(self, input_dim, output_dim):
        super().__init__()
        """
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
        """
        self.net = nn.Sequential(
            nn.Linear(input_dim, 2**10),
            nn.ReLU(),
            nn.Linear(2**10, 2**9),
            nn.ReLU(),
            nn.Linear(2**9, 2**8),
            nn.ReLU(),
            nn.Linear(2**8, 2**7),
            nn.ReLU(),
            nn.Linear(2**7, output_dim)
        )

        self.flatten = nn.Flatten()
    def forward(self, x):
        return self.net(x)

class decoder(nn.Module):
    def __init__(self, input_dim, output_dim):
        super().__init__()
        self.net = nn.Sequential(
            nn.Linear(input_dim, 2**7),
            nn.ReLU(),
            nn.Linear(2**7, 2**8),
            nn.ReLU(),
            nn.Linear(2**8, 2**9),
            nn.ReLU(),
            nn.Linear(2**9, 2**10),
            nn.ReLU(),
            nn.Linear(2**10, output_dim),
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
