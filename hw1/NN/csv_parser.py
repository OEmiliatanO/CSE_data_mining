from random import randint
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
    return (data_list,tag_list)
if __name__ == "__main__":
    csv_parser("../data/testA/train_data.csv")