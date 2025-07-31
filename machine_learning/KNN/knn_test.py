import numpy as np
from sklearn import datasets
from sklearn.model_selection import train_test_split
from matplotlib.colors import ListedColormap

# Define a custom colormap for visualization
# This colormap will be used to visualize the classes in the datasets
# The colormap will have three colors: red, green, and blue
# Each color corresponds to a class in the dataset
# Red for class 0, green for class 1, and blue for class 2
# The ListedColormap is used to create a colormap from a list of colors
# This is useful for visualizing classification results
cmap = ListedColormap(["#FF0000", "#00FF00", "#0000FF"])


# Load the iris dataset
# and split it into training and testing sets
# The iris dataset is a classic dataset for classification tasks
# It contains 150 samples of iris flowers with 4 features each
# The target variable has 3 classes: setosa, versicolor, and virginica
# We will use only the first two features for visualization purposes
iris: "datasets.Bunch" = datasets.load_iris()
X: np.ndarray = iris.data[:, :4]  # Use all four features for training
y: np.ndarray = iris.target  # Use all three classes

# Split the dataset into training and testing sets
# using a test size of 20% and a random state for reproducibility
# The train_test_split function from sklearn is used to split the dataset
# into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=1234
)


# Uncomment the following lines to visualize the dataset
import matplotlib.pyplot as plt

# Visualize the dataset using a scatter plot
# This will help us understand the distribution of the classes
plt.figure(figsize=(8, 6))
# Scatter plot of the first two features (sepal length and sepal width)
# The x-axis represents the sepal length and the y-axis represents the sepal width
# The points are colored according to their class labels
# The cmap parameter is used to specify the colormap for the points
# The edgecolor parameter is used to specify the color of the edges of the points
# The s parameter is used to specify the size of the points
plt.title("Iris Dataset Visualization")
plt.xlim(X[:, 0].min() - 1, X[:, 0].max() + 1)
plt.ylim(X[:, 1].min() - 1, X[:, 1].max() + 1)
plt.grid()
plt.xticks(np.arange(X[:, 0].min() - 1, X[:, 0].max() + 1, 0.5))
plt.yticks(np.arange(X[:, 1].min() - 1, X[:, 1].max() + 1, 0.5))
plt.scatter(X[:, 0], X[:, 1], c=y, cmap=cmap, edgecolor="k", s=20)
plt.xlabel("Sepal Length")
plt.ylabel("Sepal width")
plt.show()

# Test the KNN implementation
# Assuming the KNN class is defined in knn.py
# and the euclidean_distance function is defined in knn.py
# from knn import euclidean_distance
# from knn import KNN
from knn import KNN

knn = KNN(k=3)
knn.fit(X_train, y_train)
predictions = knn.predict(X_test)

# print(predictions)
accuracy = np.sum(predictions == y_test) / len(y_test)
print(f"Accuracy: {accuracy * 100:.2f}%")
