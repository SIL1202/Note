from sklearn import datasets
from sklearn.model_selection import train_test_split

from logistic_regression import LogisticRegression

cancer: "datasets.Bunch" = datasets.load_breast_cancer()
X = cancer.data
y = cancer.target

# check the shape of its datas
print(f"Shape of X: {X.shape}")
print(f"Shape of y: {y.shape}")

import pandas as pd

# list the datas in table form
df = pd.DataFrame(X, columns=cancer.feature_names)
print(f"DataFrame:\n {df.head()}")


from sklearn.preprocessing import StandardScaler

# Explanation:
# Standardization rescales the features so that each has a mean of 0 and a standard deviation of 1.
# This prevents features with larger scales from dominating the learning process.
# It also helps the gradient descent algorithm converge faster and more stably.
scaler = StandardScaler()
X = scaler.fit_transform(X)

# split the datas
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# start training
model = LogisticRegression()
model.fit(X_train, y_train)

import numpy as np

# predict the X_test
y_pred = model.predict(X_test)
# calculate the accuracy
accuracy = np.mean(y_pred == y_test)
print(f"Accuracy: {accuracy}")

import matplotlib.pyplot as plt

plt.plot(range(len(model.loss_history)), model.loss_history, color="blue")
plt.title("loss history")
plt.xlabel("iterations")
plt.ylabel("loss")
plt.show()

from sklearn.metrics import confusion_matrix
import seaborn as sns

cm = confusion_matrix(y_test, y_pred)
sns.heatmap(cm, annot=True, fmt="d")
plt.title("Confusion Matrix")
plt.xlabel("Predicted")
plt.ylabel("Actual")
plt.show()
