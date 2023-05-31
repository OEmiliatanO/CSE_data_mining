import torch
import torch.nn as F
import torchvision
from torch.utils.data import TensorDataset,DataLoader
import numpy as np
import pandas as pd
from model import DNN
from test import test
import matplotlib.pyplot as plt
BATCH_SIZE = 8
OUTPUT_DIM=100
DATA = "AUG3000"
train_data = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/aug_3000_train_data.csv",header=None).to_numpy()

train_label = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/aug_3000_train_label.csv",header=None).to_numpy()
tensor_train_data = torch.tensor(train_data)
tensor_train_label = torch.tensor(train_label).long()
tensor_train_label[tensor_train_label<4]=1
train_dataset = TensorDataset(tensor_train_data,tensor_train_label)
train_dataloader = DataLoader(train_dataset,batch_size=BATCH_SIZE,shuffle=True)
test_data = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/aug_0_test_data.csv",header=None).to_numpy()
test_label = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/aug_0_test_label.csv",header=None).to_numpy()
tensor_test_data = torch.tensor(test_data)

tensor_test_label = torch.tensor(test_label).long()
tensor_test_label[tensor_test_label<4]=1
tensor_test_label[tensor_test_label>=4]=0

# data = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/test_data.csv").to_numpy()
# label = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/test_label.csv").to_numpy().reshape((-1))
# print(data.shape,label.shape)
# tensor_test_data = torch.tensor(data)
# tensor_test_label = torch.tensor(label).long()
test_dataset = TensorDataset(tensor_test_data,tensor_test_label)
test_dataloader = DataLoader(test_dataset,batch_size=BATCH_SIZE)
def train(dataloader):
    


    EPOCH = 20 
    model = DNN(len(tensor_train_data[0]),OUTPUT_DIM).to("cuda")
    #model.load_state_dict(torch.load("one-class-model-from-{}.pth".format(DATA)))
    opt = torch.optim.Adam(model.parameters(),lr=1e-5,weight_decay=1e-6)
    aver_loss = []
    corr=[]
    test_acc_arr=[]
    test_loss_arr=[]

    c = torch.zeros(OUTPUT_DIM,device="cuda")
    eps = 0.0001

    n=0
    model.eval()
    with torch.no_grad():
        for data in dataloader:
            inputs,ts= data
            inputs = inputs.to(torch.float32).to("cuda")
            outcome = model(inputs)
            #print(outcome)
            n+=outcome.shape[0]
            c += torch.sum(outcome,dim=0)
    
    c/=n
    print(c)
    c[(abs(c) < eps) & (c < 0)] = -eps
    c[(abs(c) < eps) & (c > 0)] = eps
    print(c)
    np.savetxt("c_{}.txt".format(DATA),c.cpu().numpy())
    model.train()
    for epoch in range(EPOCH):
        arr = []
        r=0
        for step,(inputs,target) in enumerate(dataloader):

            inputs, target = inputs.to(torch.float32).to("cuda"), target.to("cuda")

            outcome = model(inputs)
            dist = torch.sum((outcome-c)**2,dim=1)
            
            r = max(r,torch.max(dist).item())
            # print(dist)
            loss = torch.mean(dist)
            arr.append(loss.item())
            opt.zero_grad()
            loss.backward()
            opt.step()
            if  ((step+1)*(BATCH_SIZE))%800==0:
                print("Epoch:{}, Loss={}, [{}/{}]".format(epoch+1,loss.item(),((step+1)*BATCH_SIZE),len(dataloader)*BATCH_SIZE))
        print("Training: Epoch:{} Average Loss:{}".format(epoch+1,sum(arr)/len(arr)))
        x=test(test_dataloader,c=c,model=model,r=r)
        # plt.plot(arr)
        # plt.show()
        # aver_loss.append(sum(arr)/len(arr))
        # corr.append(correct/len(dataloader.dataset))

    torch.save(model.state_dict(),"one-class-model-from-{}.pth".format(DATA))
    return x
train(train_dataloader)
