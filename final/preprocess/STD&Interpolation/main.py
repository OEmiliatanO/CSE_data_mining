import numpy as np
import pandas as pd
import sys
import math
import matplotlib.pyplot as plt
from functions import interpolate_and_add_gaussian_noise


m,n = map(int,[sys.argv[1],sys.argv[2]]) #Data Augumentation with linear interpolation and adding noise

data = pd.read_csv(sys.argv[3],header=None).to_numpy()
data = np.nan_to_num(data,nan=0.0,posinf=999999,neginf=-999999)
if("train" in sys.argv[3]):
    data = (data-np.amin(data,0))/(np.amax(data,0)-np.amin(data,0)) #normalization    
else:
    train = pd.read_csv(sys.argv[3].replace("test","train"),header=None).to_numpy()
    data = (data-np.amin(train,0))/(np.amax(train,0)-np.amin(train,0)) #normalization
data = np.nan_to_num(data,nan=0.0,posinf=999999,neginf=-999999)
if("train" in sys.argv[3]):
    data = (data-np.mean(data,axis=0))/np.std(data,axis=0) #standardlization
else:
    data = (data-np.mean(train,axis=0))/np.std(train,axis=0) #standardlization
data = np.nan_to_num(data,nan=0.0,posinf=999999,neginf=-999999)
label = pd.read_csv(sys.argv[4],header=None).to_numpy()

preprocessed_data = interpolate_and_add_gaussian_noise(m,n,data,label)
# preprocessed_data = np.nan_to_num(preprocessed_data,nan=0.0,posinf=999999,neginf=-999999)
data_name = sys.argv[5]
label_name = sys.argv[6]

np.savetxt(data_name, preprocessed_data[0], delimiter = ',')
np.savetxt(label_name, preprocessed_data[1], delimiter = ',')



#python main.py 1000 0 ../../data/gene_expression_cancer_RNA-Seq_data_set/train_data.csv ../../data/gene_expression_cancer_RNA-Seq_data_set/train_label.csv ../../data/gene_expression_cancer_RNA-Seq_data_set/aug_0_train_data.csv ../../data/gene_expression_cancer_RNA-Seq_data_set/aug_0_train_label.csv
#python main.py 0 0 ../../data/gene_expression_cancer_RNA-Seq_data_set/test_data.csv ../../data/gene_expression_cancer_RNA-Seq_data_set/test_label.csv ../../data/gene_expression_cancer_RNA-Seq_data_set/aug_0_test_data.csv ../../data/gene_expression_cancer_RNA-Seq_data_set/aug_0_test_label.csv

