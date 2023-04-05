from random import randint
import torch
import numpy as np
from csv_parser import csv_parser
from torch.utils.data import TensorDataset,DataLoader
from sa import sa
class NN(torch.nn.Module):
    def __init__(self,layer_nums):
        super(NN,self).__init__()
        self.layer_nums=[8]+layer_nums+[2]
        self.nn = torch.nn.ModuleList([torch.nn.Linear(self.layer_nums[i],self.layer_nums[i+1]) for i in range(len(self.layer_nums)-1)])
        self.acti=torch.nn.ReLU()
        # self.nn=torch.nn.Sequential(
        #     torch.nn.Linear(8,16),
        #     torch.nn.Linear(16,32),
        #     torch.nn.Linear(32,64),
        #     torch.nn.Linear(64,128),
        #     torch.nn.ReLU(),
        #     torch.nn.Linear(128,256),
        #     torch.nn.ReLU(),
        #     torch.nn.Linear(256,128),
        #     torch.nn.ReLU(),
        #     torch.nn.Linear(128,64),
        #     torch.nn.Linear(64,32),
        #     torch.nn.Linear(32,16),
        #     torch.nn.Linear(16,8),
        #     torch.nn.Linear(8,4),
        #     torch.nn.Linear(4,2),
        # )

    def forward(self,x):
        for f in self.nn:
            x = f(x)
            if randint(0,1):
               x = self.acti(x)
        return x



BATCH_SIZE=8
NUM_WORKER=4

def main():
    #Data import to dataset and dataloader
    train_data_A_dir="../data/testA/train_data.csv"
    train_data,train_tag=csv_parser(train_data_A_dir)
    tensor_train_data=torch.tensor(train_data)
    tensor_train_tag=torch.tensor(train_tag)
    train_dataset=TensorDataset(tensor_train_data,tensor_train_tag)

    

    train_dataloader=DataLoader(dataset=train_dataset,batch_size=BATCH_SIZE,num_workers=NUM_WORKER)
    test_data_A_dir="../data/testA/test_data.csv"
    test_data,test_tag=csv_parser(test_data_A_dir)
    tensor_test_data=torch.tensor(test_data)
    tensor_test_tag=torch.tensor(test_tag)
    test_dataset=TensorDataset(tensor_test_data,tensor_test_tag)
    test_dataloader=DataLoader(test_dataset,batch_size=BATCH_SIZE)
    
    

    def train(solu,output_mode=False):
        model=NN(solu).to("cuda")
        if output_mode:
            EPOCH=100
        else:
            EPOCH=5


        opt = torch.optim.Adam(model.parameters(), lr=1e-4)
        loss_fn = torch.nn.CrossEntropyLoss()
        min_loss=9999
        for epoch in range(EPOCH):
            for step,(inputs,target) in enumerate(train_dataloader):
                
                inputs, target = inputs.to("cuda"), target.to("cuda")
                
                outcome = model(inputs)
                
                # print(outcome.size(),target.size())
                loss = loss_fn(outcome,target)
                opt.zero_grad()
                loss.backward()
                opt.step()

                # print("Epoch:{}, Loss={}, [{}/{}]".format(epoch+1,loss.item(),((step+1)*BATCH_SIZE),len(train_dataloader)*BATCH_SIZE))
            size = len(test_dataloader.dataset)
            num_batches = len(test_dataloader)
            model.eval()
            test_loss,correct=0,0
            with torch.no_grad():
                for inputs,target in test_dataloader:
                    inputs,target=inputs.to("cuda"),target.to("cuda")
                    pred = model(inputs)
                    test_loss += loss_fn(pred,target).item()
                    correct += (pred.argmax(1) == target).type(torch.float).sum().item()
            test_loss /= num_batches
            correct /= size
            print(f"Test Error: \n Accuracy: {(100*correct):>0.8f}%, Avg loss: {test_loss:>8f} \n")
            if output_mode and min_loss>test_loss:
                min_loss=test_loss
                torch.save(model,"diabete_model.pth")
        if not output_mode:
            return test_loss
    #SA parameter
    N=10
    MAXT=0.1
    MINT=0.001
    RATE=0.995
    K=2
    LNMA=256 #max number of node in a layer
    LNMI=16 #max number of node in a layer

    #SA
    # solution=sa(N,MAXT,MINT,RATE,K,LNMA,LNMI,train)
    solution=[31,110,253,240,223,99,212,163,243,73]
    train(solution,output_mode=True)
    
if __name__ == "__main__":
    main()