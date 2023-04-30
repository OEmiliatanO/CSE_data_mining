import sys
import torch
from Autoencoder import autoencoder
import pandas as pd

input_dim = int(sys.argv[1])
output_dim = int(sys.argv[2])
encoder = autoencoder(input_dim, output_dim)

