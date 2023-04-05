from random import randint
import numpy as np
TYPE_FUNC=[float,float,float,float,float,float,float,float,int]
def type_convert(li):
    for i,j in enumerate(li): 
        li[i]=TYPE_FUNC[i](j)
def empty_data_remove(li):
    for i,j in enumerate(li[:-1]):
        # print(j)
        if li[i]==0:
            
            if(i==1):
                if(li[-1]==0):
                    li[i]=float(randint(70,99))
                if(li[-1]==1):
                    li[i]=float(randint(100,180))
            if(i==2):
                li[i]=float(randint(80,160))
            if(i==3):
                li[i]=float(randint(15,50))
            if(i==4):
                if(li[-1]==0):
                    li[i]=float(randint(80,160))
                if(li[-1]==1):
                    li[i]=float(randint(200,300))
            if(i==5):
                li[i]=float(randint(180,450))
            # print(li)
            
def normalization(data_list):
    np_li=np.array(data_list)
    np_li_max=np_li.max(0)
    np_li_min=np_li.min(0)
    for data in data_list:
        for ind,ite in enumerate(data):
            data[ind]=float((ite-np_li_min[ind])/(np_li_max[ind]-np_li_min[ind]))        

def standardization(data_list):
    np_li=np.array(data_list)
    std=np.std(np_li,1,ddof=1)
    mean=np.mean(np_li,1)
    for data in data_list:
        for ind,ite in enumerate(data):
            data[ind]=float((ite-mean[ind])/std[ind])
def csv_parser(dir):
    with open(dir,"r") as f:
        raw_data=f.read()
        line_data=raw_data.split("\n")
        data_list=[]
        tag_list=[]
        for data in line_data[1:-1]:
            li=data.split(",")
            type_convert(li)
            empty_data_remove(li)
            data_list.append(li[:-1])
            tag_list.append(li[-1])
        normalization(data_list)
        standardization(data_list)
        # print(data_list)
        
        # print(type(data_list[0][0]))
    return (data_list,tag_list)
if __name__ == "__main__":
    csv_parser("../data/testA/train_data.csv")