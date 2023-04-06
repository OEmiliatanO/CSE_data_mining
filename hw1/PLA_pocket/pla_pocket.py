import pandas as pd
import time
from sklearn.linear_model import Perceptron
from sklearn import preprocessing
import numpy as np

# input the data
while 1:
    AorB = input('Select your data (A or B ?) : ')
    if (AorB == 'A' or AorB == 'B' or AorB == 'a' or AorB == 'b'):
        break
    else:
        continue
if (AorB == 'A' or AorB == 'a'):
    train_data = pd.read_csv('../data/testA/train_data.csv')
    test_data = pd.read_csv('../data/testA/test_data.csv')
else:
    train_data = pd.read_csv('../data/testB/train_data.csv')
    test_data = pd.read_csv('../data/testB/test_data.csv')

num_test = input('Number of tests: ')
num_test = int(num_test)
i = 0
sum_accuracy = 0
sum_search_time = 0
array = np.array([0.0 for i in range(num_test)])
while i < num_test:

    X_train = train_data.iloc[:,:-1].values
    X_test = test_data.iloc[:,:-1].values
    y_train = train_data.iloc[:,-1].values
    y_test = test_data.iloc[:,-1].values

    clf = Perceptron()
    # train model
    clf.fit(X_train, y_train)
    # calculate accuracy
    start = time.time()
    accuracy = clf.score(X_test, y_test)
    end = time.time()
    search_time = end - start
    sum_search_time += search_time
    # sum_accuracy += accuracy
    array[i] = accuracy
    i += 1

avg_accuracy = array.mean()
std_accuracy = array.std()
normalized_arr = preprocessing.normalize([array])
avg_nor_acc = normalized_arr.mean()
std_nor_acc = normalized_arr.std()
print(f"Using data {AorB}.")
print(f"The {num_test} times average search time: {sum_search_time / num_test:.5f}")
print(f"The {num_test} times average accuracy rate: {avg_accuracy:.5f}")
print(f"The {num_test} times standard deviation of accuracy rate: {std_accuracy:.5f}")
print(f"The {num_test} times average normalized accuracy rate: {avg_nor_acc:.5f}")
print(f"The {num_test} times standard deviation of normalized accuracy rate: {std_nor_acc / num_test:.5f}")
