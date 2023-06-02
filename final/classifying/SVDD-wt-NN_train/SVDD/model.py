import torch
import torch.nn as F
import math
class DNN(torch.nn.Module):
    def __init__(self,input_dim,output_dim):
        super(DNN,self).__init__()
        lower_bound = 2**5
        self.base = 2 # 2**math.floor(math.log2(input_dim))//2**9
        if self.base < lower_bound:
            self.base = lower_bound
        #self.layer_nums = [input_dim]+[self.base,self.base*2]+[self.base*4 for i in range(0)]+[self.base*2,self.base]+[output_dim]
        self.layer_nums = [input_dim]+[5]+[output_dim]
        self.li=[F.Linear(self.layer_nums[i],self.layer_nums[i+1],bias=1) for i in range(len(self.layer_nums)-1)]
        self.bn=[F.BatchNorm1d(i) for i in self.layer_nums[1:]]
        self.lin = F.ModuleList(self.li)
        self.bnn = F.ModuleList(self.bn)
        self.acti = F.ELU()
        self.dropout = F.Dropout(p=0.3)
        self.r = None
    def forward(self,x):
        for i in range(len(self.bn)-1):
            x = self.dropout(x)
            x = self.lin[i](x)
           # x = self.bnn[i](x)
            x = self.acti(x)
        return self.lin[-1](x)
    def set_r(self,r):
        self.r = r
        
