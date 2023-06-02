import torch
import torch.nn as F
import torchvision
from torch.utils.data import TensorDataset,DataLoader
import numpy as np
import pandas as pd
from model import DNN,SVDD
import time
import sys
BATCH_SIZE = 8
OUTPUT_DIM= 200
DATA = "PCA100"

def SVDDNN(data_path,label_path,outcome_path):
    test_data = pd.read_csv(data_path,header=None).to_numpy()
    test_label = pd.read_csv(label_path,header=None).to_numpy()
    tensor_test_data = torch.tensor(test_data)

    tensor_test_label = torch.tensor(test_label).long()
    tensor_test_label[tensor_test_label<4]=1
    tensor_test_label[tensor_test_label>=4]=0
    test_dataset = TensorDataset(tensor_test_data,tensor_test_label)

    dataloader = DataLoader(test_dataset,batch_size=BATCH_SIZE)
    SVDD_model = SVDD(len(test_dataset[0][0]),OUTPUT_DIM).to("cuda")
    SVDD_model.load_state_dict(torch.load('./model/one-class-model-from-{}.pth'.format(DATA)))
    c = torch.tensor(pd.read_csv("./parameter/c.txt",header=None).to_numpy()).squeeze().to(torch.float32).to("cuda")
    arr = []

    st = time.time()
    with torch.no_grad():
        for step,(inputs,target) in enumerate(dataloader):
            inputs, target = inputs.to(torch.float32).to("cuda"), target.to("cuda")
            outcome = SVDD_model(inputs)
            # a = torch.nn.functional.softmax(outcome,dim=1)
            # print(a.max(dim=1),target)
            dist = torch.sum((outcome-c)**2,dim=1)
            arr.extend(list(zip(dist.cpu().numpy().tolist(),target.cpu().numpy().tolist())))

    r = pd.read_csv("./parameter/r.txt",header = None).to_numpy()[0]
    cnt = 0
    li = []
    for dist,label in arr:
        if dist > r:
            ans = 0
        else:
            ans = 1
        li.append(ans)
        cnt += ans != label[0]
        if ans != label[0]:
            print(dist)
    print("Finished")
    print("SVDD Accuracy:{:.6f}%".format((len(arr)-cnt)/len(arr)*100))

    li = np.array(li)

    tensor_test_data = torch.tensor(test_data)
    tensor_test_label = torch.tensor(test_label).squeeze().long()
    tensor_test_data=tensor_test_data[li == 1]
    tensor_test_label=tensor_test_label[li == 1]
    tensor_test_label[tensor_test_label>=4] = 0
    test_dataset = TensorDataset(tensor_test_data,tensor_test_label)
    dataloader = DataLoader(test_dataset,batch_size=BATCH_SIZE)

    CANCER_OUTPUT_DIM=4
    model = DNN(len(tensor_test_data[0]),CANCER_OUTPUT_DIM).to("cuda")
    model.load_state_dict(torch.load('./model/classifying-model-from-{}.pth'.format(DATA)))


    loss_fn = F.CrossEntropyLoss()
    correct=0
    all_loss=0
    model.eval()
    with torch.no_grad():
        for step,(inputs,target) in enumerate(dataloader):
            inputs, target = inputs.to(torch.float32).to("cuda"), target.to("cuda")
            outcome = model(inputs)
            
            # a = torch.nn.functional.softmax(outcome,dim=1)
            # print("target",target)
            loss = loss_fn(outcome,target)
            all_loss+=loss.item()
            correct += (outcome.argmax(1) == target).type(torch.float).sum().item()
    print("Accuracy(only known):{:.6f}%".format(correct/len(dataloader.dataset)*100))

    et = time.time()

    arr = []

    for i in range(len(test_data)):
        data,label=test_data[i],li[i]
        if label==0:
            arr.append(0)
        else:
            outcome = model(torch.tensor(data).to(torch.float32).to("cuda"))
            a = outcome.argmax().item()
            arr.append(a)
    print("Write csv",outcome_path)
    np.savetxt(outcome_path,arr,fmt="%i",delimiter=",")

    print("Time:{}s".format(et-st))
SVDDNN(sys.argv[1],sys.argv[2],sys.argv[3])