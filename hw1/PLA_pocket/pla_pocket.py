import pandas as pd
import numpy as np
from sklearn.linear_model import Perceptron

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
while i < num_test:

    X_train = train_data.iloc[:,:-1].values
    X_test = test_data.iloc[:,:-1].values
    y_train = train_data.iloc[:,-1].values
    y_test = test_data.iloc[:,-1].values

    clf = Perceptron()
    # train model
    clf.fit(X_train, y_train)
    # calculate accuracy
    accuracy = clf.score(X_test, y_test)
    sum_accuracy += accuracy
    i += 1

print(f"Using data {AorB}. The {num_test} times average accuracy rate: {sum_accuracy / num_test:.5f}")
