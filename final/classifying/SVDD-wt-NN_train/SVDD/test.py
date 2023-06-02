import torch
import torch.nn as F
import torchvision
from torch.utils.data import TensorDataset,DataLoader
import numpy as np
import pandas as pd
from model import DNN
import matplotlib.pyplot as plt
BATCH_SIZE = 8
CANCER_OUTPUT_DIM=4
DATA = "AUG3000"
# data = pd.read_csv("../../data/gene_expression_cancer_RNA-Seq_data_set/train_data.csv").to_numpy()
# label = pd.read_csv("../../data/gene_expression_cancer_RNA-Seq_data_set/train_label.csv").to_numpy().reshape((-1))
# print(data.shape,label.shape)
# tensor_test_data = torch.tensor(data)
# tensor_test_label = torch.tensor(label).long()


def test(dataloader=None,c=None,r=None,model=None,from_train=True):
    if not dataloader:
        test_data = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/aug_0_test_data.csv",header=None).to_numpy()
        test_label = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/aug_0_test_label.csv",header=None).to_numpy()
        tensor_test_data = torch.tensor(test_data)
        tensor_test_label = torch.tensor(test_label).long()
        tensor_test_label[tensor_test_label<4]=1
        tensor_test_label[tensor_test_label>=4]=0
        test_dataset = TensorDataset(tensor_test_data,tensor_test_label)
        

        dataloader = DataLoader(test_dataset,batch_size=BATCH_SIZE)
    if not model:
        model = DNN(len(test_dataset[0][0]),len(test_dataset[0][0])).to("cuda")
        model.load_state_dict(torch.load('one-class-model-from-{}.pth'.format(DATA)))
    if c==None:
        c = torch.tensor(pd.read_csv("c_{}.txt".format(DATA),header=None).to_numpy()).squeeze().to(torch.float32).to("cuda")
        # print(c.shape)
        # c = torch.zeros(len(tensor_test_data[0]),device="cuda")
        # print(c.shape)
        

    correct=0
    arr = []
    with torch.no_grad():
        for step,(inputs,target) in enumerate(dataloader):
            inputs, target = inputs.to(torch.float32).to("cuda"), target.to("cuda")
            outcome = model(inputs)
            # a = torch.nn.functional.softmax(outcome,dim=1)
            # print(a.max(dim=1),target)
            dist = torch.sum((outcome-c)**2,dim=1)
            arr.extend(list(zip(dist.cpu().numpy().tolist(),target.cpu().numpy().tolist())))
            loss = torch.mean(dist)
            if(step == 0):
                print("average distance:",dist)
            if(step == len(dataloader)-1):
                print("average distance:",dist)

            thre = torch.mean(dist) - 3*torch.std(dist)
            # pred = dist
            # pred[pred<thre]=0
            # pred[pred>thre]=1
            # correct += (outcome.argmax(1) == target).type(torch.float).sum().item()
            # print("Dist=  {}\n,Target={}\n,Pred  ={}, [{}/{}]".format(dist,target,pred,((step+1)*BATCH_SIZE),len(dataloader)*BATCH_SIZE))
            #print("Dist=  {}\n,Target={}\n, [{}/{}]".format(dist,target,((step+1)*BATCH_SIZE),len(dataloader)*BATCH_SIZE))
    if from_train:
        print("r",r)
        np.savetxt("r_{}.txt".format(DATA),[r+0.000001])
        flag = False
        cnt =0
        for dist,label in arr:
            if dist > r:
                t = 0
            else:
                t = 1
            if label[0]!=t :
                cnt+=1
    else:
        r = pd.read_csv("r_{}.txt".format(DATA),header = None).to_numpy()[0]
        cnt = 0
        li = []
        for i,j in arr:
            if i<r:
                ans = 1
            else:
                ans = 0
            li.append(ans)
            cnt += ans != j[0]
            if ans != j[0]:
                print(i)
        print("Write csv","../known_unknown_clustering_{}.csv".format(DATA))
        np.savetxt("../known_unknown_clustering_{}.csv".format(DATA),np.array(li,dtype=np.int8),delimiter=",")
        print("Finished")
    print("Accuracy:{}".format((len(arr)-cnt)/len(arr)))
    return (len(arr)-cnt)/len(arr)
if __name__ == "__main__":
    test(from_train=False)
