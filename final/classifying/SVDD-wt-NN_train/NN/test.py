import torch
import torch.nn as F
import torchvision
from torch.utils.data import TensorDataset,DataLoader
import numpy as np
import pandas as pd
from model import DNN
import matplotlib.pyplot as plt
DATA = "AUG3000"
BATCH_SIZE = 8
CANCER_OUTPUT_DIM=4
test_data = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/aug_0_test_data.csv",header=None).to_numpy()
test_label = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/aug_0_test_label.csv",header=None).to_numpy().squeeze()
  
known = pd.read_csv("../known_unknown_clustering_PCA100.csv",header=None).to_numpy().reshape(-1)
test_data=test_data[known == 1]
test_label=test_label[known == 1]
tensor_test_data = torch.tensor(test_data)
tensor_test_label = torch.tensor(test_label).long()
test_dataset = TensorDataset(tensor_test_data,tensor_test_label)
dataloader = DataLoader(test_dataset,batch_size=BATCH_SIZE)

def test(dataloader,model=None,write_csv=False):
    if not model:
        model = DNN(len(tensor_test_data[0]),CANCER_OUTPUT_DIM).to("cuda")
        model.load_state_dict(torch.load('classifying-model-from-{}.pth'.format(DATA)))
    

    loss_fn = F.CrossEntropyLoss()
    correct=0
    all_loss=0
    model.eval()
    print("Test:")
    with torch.no_grad():
        for step,(inputs,target) in enumerate(dataloader):
            inputs, target = inputs.to(torch.float32).to("cuda"), target.to("cuda")
            outcome = model(inputs)
            
            # a = torch.nn.functional.softmax(outcome,dim=1)
            # print("target",target)
            loss = loss_fn(outcome,target)
            all_loss+=loss.item()
            correct += (outcome.argmax(1) == target).type(torch.float).sum().item()
            print("Loss={}, [{}/{}]".format(loss.item(),((step+1)*BATCH_SIZE),len(dataloader)*BATCH_SIZE))
    print("Accuracy:{:.1f}%, Loss:{}".format(correct/len(dataloader.dataset)*100,all_loss/(len(dataloader.dataset))))
    if write_csv == True:
        arr = []
        test_data = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/PCA_test_data_100.csv",header=None).to_numpy()
        test_label = pd.read_csv("../../../data/gene_expression_cancer_RNA-Seq_data_set/test_label.csv",header=None).to_numpy().squeeze()
        for i in range(len(test_data)):
            data,label=test_data[i],known[i]
            if label==0:
                arr.append(0)
            else:
                outcome = model(torch.tensor(data).to(torch.float32).to("cuda"))
                a = outcome.argmax().item()
                arr.append(a)
        print("Write csv","../classified-label-for-{}.csv".format(DATA))
        np.savetxt("../classified-label-for-{}.csv".format(DATA),arr,fmt="%i",delimiter=",")

    return (correct/len(dataloader.dataset)*100,all_loss/(len(dataloader.dataset)))

if __name__ == "__main__":
    test(dataloader=dataloader,write_csv=True)
