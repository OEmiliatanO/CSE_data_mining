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
CANCER_OUTPUT_DIM=4
DATA = "AUG3000"

train_data = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/aug_3000_train_data.csv",header=None).to_numpy()
train_label = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/aug_3000_train_label.csv",header=None).to_numpy().squeeze()
print(train_data.shape)
tensor_train_data = torch.tensor(train_data)
tensor_train_label = torch.tensor(train_label).long()
train_dataset = TensorDataset(tensor_train_data,tensor_train_label)
train_dataloader = DataLoader(train_dataset,batch_size=BATCH_SIZE,shuffle=True)
test_data = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/aug_0_test_data.csv",header=None).to_numpy()
test_label = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/aug_0_test_label.csv",header=None).to_numpy().squeeze()
known = pd.read_csv("../known_unknown_clustering_{}.csv".format(DATA),header=None).to_numpy().reshape(-1)
test_data=test_data[known == 1]
test_label=test_label[known == 1]
tensor_test_data = torch.tensor(test_data)
tensor_test_label = torch.tensor(test_label).long()
test_dataset = TensorDataset(tensor_test_data,tensor_test_label)


# data = pd.read_csv("../../data/gene_expression_cancer_RNA-Seq_data_set/test_data.csv").to_numpy()
# label = pd.read_csv("../../data/gene_expression_cancer_RNA-Seq_data_set/test_label.csv").to_numpy().reshape((-1))
# print(data.shape,label.shape)
# tensor_test_data = torch.tensor(data)
# tensor_test_label = torch.tensor(label).long()
test_dataset = TensorDataset(tensor_test_data,tensor_test_label)
test_dataloader = DataLoader(test_dataset,batch_size=BATCH_SIZE)
def train(dataloader):
    EPOCH = 30
    model = DNN(len(tensor_train_data[0]),CANCER_OUTPUT_DIM).to("cuda")
    print(model)
    loss_fn = F.CrossEntropyLoss()
    opt = torch.optim.Adam(model.parameters(),lr=1e-4)
    aver_loss = []
    corr=[]
    test_acc_arr=[]
    test_loss_arr=[]
    model.train()
    for epoch in range(EPOCH):
        arr = []
        correct=0
        for step,(inputs,target) in enumerate(dataloader):

            inputs, target = inputs.to(torch.float32).to("cuda"), target.to("cuda")
            # print(inputs.size(),target.size())
            outcome = model(inputs)
            # print(outcome.size())
            loss = loss_fn(outcome,target)
            correct += (outcome.argmax(1) == target).type(torch.float).sum().item()
            arr.append(loss.item())
            opt.zero_grad()
            loss.backward()
            opt.step()
            print("Epoch:{}, Loss={}, [{}/{}]".format(epoch+1,loss.item(),((step+1)*BATCH_SIZE),len(dataloader)*BATCH_SIZE))
        print("Training: Epoch:{} Average Loss:{} Accuracy:{:>0.1f}%".format(epoch+1,sum(arr)/len(arr),correct/len(dataloader.dataset)*100))

        # plt.plot(arr)
        # plt.show()
        aver_loss.append(sum(arr)/len(arr))
        corr.append(correct/len(dataloader.dataset))

        test_acc,test_loss=test(test_dataloader,model)
        test_acc_arr.append(test_acc)
        test_loss_arr.append(test_loss)
    # plt.plot(aver_loss)
    # plt.plot(test_loss_arr)
    # plt.xlabel("Epoch")
    # plt.ylabel("loss")
    # plt.show()
    # plt.plot(corr)
    # plt.plot(test_acc_arr)
    # plt.xlabel("Epoch")
    # plt.ylabel("accuracy")
    # plt.show()
    torch.save(model.state_dict(),"classifying-model-from-{}.pth".format(DATA))

train(train_dataloader)
