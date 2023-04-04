import pandas as pd
from sklearn.linear_model import Perceptron
import matplotlib.pyplot as plt
import numpy as np


train_data = pd.read_csv('train_data.csv')
test_data = pd.read_csv('test_data.csv')

# 從資料中分離出特徵和標籤
X_train = train_data.iloc[:, :-1]
y_train = train_data.iloc[:, -1]
X_test = test_data.iloc[:, :-1]
y_test = test_data.iloc[:, -1]

# 建立 Perceptron 模型
clf = Perceptron()

# 訓練模型
clf.fit(X_train, y_train)

# 評估模型
accuracy = clf.score(X_test, y_test)
print("Accuracy:", accuracy)

# plot hyperplane
w = clf.coef_[0]
b = clf.intercept_[0]
X_min = X_train.min() - 1
X_max = X_train.max() + 1

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.scatter(X_train.iloc[:, 0], X_train.iloc[:, 1], X_train.iloc[:, 2], c=y_train)

# 網格
xx, yy = np.meshgrid(np.arange(X_min[0], X_max[0], 0.2), 
                     np.arange(X_min[1], X_max[1], 0.2))
zz = (-w[0]*xx - w[1]*yy - b) / w[2]

# hyperplane
ax.plot_surface(xx, yy, zz, alpha=0.6)

# xyz axis
ax.set_xlabel('X1')
ax.set_ylabel('X2')
ax.set_zlabel('X3')

plt.show()
