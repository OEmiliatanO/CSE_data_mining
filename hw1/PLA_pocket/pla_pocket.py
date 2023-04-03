import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

# input the data
train_data = pd.read_csv('train_data.csv')
test_data = pd.read_csv('test_data.csv')
X_train = train_data.iloc[:,:-1].values
X_test = test_data.iloc[:,:-1].values
y_train = train_data.iloc[:,-1].values
y_test = test_data.iloc[:,-1].values

# add bias term
X_train = np.insert(X_train, 0, 1, axis=1)
X_test = np.insert(X_test, 0, 1, axis=1)

# initialize weights
w = np.zeros(X_train.shape[1])

# Pocket Perceptron Learning Algorithm
num_iterations = 1000
min_error = len(y_train)
best_w = w
for i in range(num_iterations):
    y_pred = np.sign(X_train.dot(w))
    errors = (y_pred != y_train)
    num_errors = errors.sum()
    if num_errors < min_error:
        min_error = num_errors
        best_w = w
    if num_errors == 0:
        break
    random_index = np.random.choice(np.where(errors)[0])
    w = w + y_train[random_index] * X_train[random_index]

# predict labels for test data
y_pred = np.sign(X_test.dot(best_w))

# calculate accuracy
accuracy = (y_pred == y_test).mean()
print(f"Accuracy: {accuracy:.5f}")

# # plot data points and decision boundary
# plt.scatter(X_train[:,1], X_train[:,2], c=y_train, cmap=plt.cm.Paired, edgecolors='k')
# x1_min, x1_max = np.concatenate((X_train[:,1], X_test[:,1])).min(), np.concatenate((X_train[:,1], X_test[:,1])).max()
# x2_min, x2_max = np.concatenate((X_train[:,2], X_test[:,2])).min(), np.concatenate((X_train[:,2], X_test[:,2])).max()
# xx1, xx2, xx3, xx4, xx5, xx6, xx7, xx8 = np.meshgrid(np.linspace(x1_min, x1_max), np.linspace(x2_min, x2_max), np.linspace(np.concatenate((X_train[:,3], X_test[:,3])).min(), np.concatenate((X_train[:,3], X_test[:,3])).max()), np.linspace(np.concatenate((X_train[:,4], X_test[:,4])).min(), np.concatenate((X_train[:,4], X_test[:,4])).max()), np.linspace(np.concatenate((X_train[:,5], X_test[:,5])).min(), np.concatenate((X_train[:,5], X_test[:,5])).max()), np.linspace(np.concatenate((X_train[:,6], X_test[:,6])).min(), np.concatenate((X_train[:,6], X_test[:,6])).max()), np.linspace(np.concatenate((X_train[:,7], X_test[:,7])).min(), np.concatenate((X_train[:,7], X_test[:,7])).max()), np.linspace(np.concatenate((X_train[:,8], X_test[:,8])).min(), np.concatenate((X_train[:,8], X_test[:,8])).max()))
# X_grid = np.column_stack((np.ones(xx1.ravel().shape), xx1.ravel(), xx2.ravel(), xx3.ravel(), xx4.ravel(), xx5.ravel(), xx6.ravel(), xx7.ravel(), xx8.ravel()))
# y_grid = np.sign(X_grid.dot(best_w))

# # plot decision boundary and margins
# plt.contourf(xx1, xx2, y_grid.reshape(xx1.shape), cmap=plt.cm.Paired, alpha=0.2)
# plt.contour(xx1, xx2, y_grid.reshape(xx1.shape), colors='k', levels=[-1, 0, 1], alpha=0.5, linestyles=['--', '-', '--'])
# plt.xlim(xx1.min(), xx1.max())
# plt.ylim(xx2.min(), xx2.max())
# plt.xlabel('Feature 1')
# plt.ylabel('Feature 2')
# plt.title('Pocket Perceptron Learning Algorithm')
# plt.show()
