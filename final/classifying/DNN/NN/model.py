import torch
import torch.nn as F
import math
class DNN(torch.nn.Module):
    def __init__(self,input_dim,output_dim):
        super(DNN,self).__init__()
        base = 2**math.floor(math.log2(input_dim))//32
        lower_bound = 128 // 32 #//32 for aug
        if base  < lower_bound:
            base = lower_bound
        self.layer_nums = [input_dim]+[base,base*2]+[base*4 for i in range(20)]+[base*2,base]+[output_dim]
        self.nn = F.ModuleList([torch.nn.Linear(self.layer_nums[i],self.layer_nums[i+1]) for i in range(len(self.layer_nums)-1)])
        self.acti = F.ReLU()
    def forward(self,x):
        for f in self.nn[:-1]:
            x = f(x)
            x = self.acti(x)
        return self.nn[-1](x)
