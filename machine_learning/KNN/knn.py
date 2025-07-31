# K-Nearest Neighbors (KNN) Classifier Implementation
import numpy as np
from collections import Counter


# using Euclidean distance as the metric for similarity
def euclidean_distance(x1, x2):
    return np.sqrt(np.sum((x1 - x2) ** 2))


# KNN Classifier
# k is the number of neighbors to consider
# fit method takes training data and labels
# predict method takes test data and returns predicted labels
# _predict_single method predicts the label for a single instance
# using the k nearest neighbors from the training data
# Counter is used to find the most common label among the k nearest neighbors
class KNN:
    def __init__(self, k=3) -> None:
        self.k = k

    def fit(self, X, y):
        self.X_train = X
        self.y_train = y

    def predict(self, y):
        predictions = [self._predict_single(x) for x in y]
        return np.array(predictions)

    def _predict_single(self, x):
        # calculate all x from all other X_train

        distances = [euclidean_distance(x, x_train) for x_train in self.X_train]

        # sort the distances and return the indices of the k nearest neighbors
        k_indices = np.argsort(distances)[: self.k]
        sorted_labels = [self.y_train[i] for i in k_indices]

        # return the most common class sorted_labels
        most_common = Counter(sorted_labels).most_common(1)
        return most_common[0][0] if most_common else None
