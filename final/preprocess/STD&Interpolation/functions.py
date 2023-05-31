import numpy as np
import random
import math
def interpolate_and_add_gaussian_noise(num_i,num_g,data,label,mu=0,sigma=0.1):
    if(num_g==num_i==0):
        return (data,label)
    dic={}
    for i in label:
        try:
            dic[int(i)]+=1
        except:
            dic[int(i)]=1
    idx = len(data)
    new_data = np.concatenate((data,np.zeros((num_i+num_g-len(data),len(data[0])))))
    new_label = np.concatenate((label,np.zeros((num_i+num_g-len(label),len(label[0])))))
    base = 0
    print(dic)
    for i in dic:
        sample_array = [j for j in range(dic[i])]
        for j in range(num_i//len(dic)-dic[i]):
            s1,s2 = random.sample(sample_array,2)
            new_data[idx]=(data[s1+base]+data[s2+base])/2
            new_label[idx]=np.array([i],dtype=np.int64)
            idx+=1
        print("inter")
        for j in range(num_g//len(dic)):
            rd_num = random.randint(base,base+dic[i]-1)
            new_data[idx] = data[rd_num]+np.array([np.random.normal(mu,sigma) for k in range(len(data[0]))])
            new_label[idx]=np.array([i],dtype=np.int64)
            idx+=1
        base += dic[i]
        print("gau")

    return (new_data,new_label)
