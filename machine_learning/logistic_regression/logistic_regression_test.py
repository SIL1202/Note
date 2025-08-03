from sklearn import datasets
from sklearn.model_selection import train_test_split
from logistic_regression import LogisticRegression  # Your custom implementation

# Load breast cancer dataset
cancer: "datasets.Bunch" = datasets.load_breast_cancer()
X = cancer.data  # Features (30-dimensional)
y = cancer.target  # Labels (0 = malignant, 1 = benign)

# Check the shape of the dataset
print(f"Shape of X: {X.shape}")  # (569, 30)
print(f"Shape of y: {y.shape}")  # (569,)

import pandas as pd

# Display the first few rows as a table
df = pd.DataFrame(X, columns=cancer.feature_names)
print(f"DataFrame:\n {df.head()}")

from sklearn.preprocessing import StandardScaler

# Standardization:
# Rescales the features so that each one has mean = 0 and std = 1.
# This helps gradient descent converge more quickly and prevents large features from dominating.
scaler = StandardScaler()
X = scaler.fit_transform(X)

# Split the dataset into training and testing sets (80% train, 20% test)
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42
)

# Create and train the model
model = LogisticRegression()
model.fit(X_train, y_train)

import numpy as np

# Make predictions on the test set
y_pred = model.predict(X_test)

# Calculate accuracy score
accuracy = np.mean(y_pred == y_test)
print(f"LR classification accuracy: {accuracy}")

import matplotlib.pyplot as plt

# Plot the learning curve (loss over iterations)
plt.plot(range(len(model.loss_history)), model.loss_history, color="blue")
plt.title("Loss History")
plt.xlabel("Iterations")
plt.ylabel("Loss")
plt.grid(True)
plt.show()

from sklearn.metrics import confusion_matrix
import seaborn as sns

# Visualize the confusion matrix
cm = confusion_matrix(y_test, y_pred)
sns.heatmap(cm, annot=True, fmt="d", cmap="Blues")
plt.title("Confusion Matrix")
plt.xlabel("Predicted Label")
plt.ylabel("True Label")
plt.show()
