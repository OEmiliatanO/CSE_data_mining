import torch
from csv_parser import csv_parser
from NN_train import NN,BATCH_SIZE
from torch.utils.data import TensorDataset,DataLoader


test_data_A_dir="../data/testA/test_data.csv"

test_data,test_tag=csv_parser(test_data_A_dir)
tensor_test_data=torch.tensor(test_data)
tensor_test_tag=torch.tensor(test_tag)
test_dataset=TensorDataset(tensor_test_data,tensor_test_tag)

test_dataloader=DataLoader(test_dataset,batch_size=BATCH_SIZE)

# model=NN([52, 229, 230, 74, 105, 151, 50, 191, 161, 168]).to("cuda")
model=torch.load('diabete_model.pth')

loss_fn = torch.nn.CrossEntropyLoss()
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
print(f"Test Error: \n Accuracy: {(100*correct):>0.1f}%, Avg loss: {test_loss:>8f} \n")