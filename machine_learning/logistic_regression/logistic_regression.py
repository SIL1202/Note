import numpy as np


class LogisticRegression:
    """
    Logistic Regression classifier implemented from scratch using gradient descent.

    Attributes:
        lr (float): Learning rate for gradient descent.
        it (int): Number of iterations for training.
        weights (np.ndarray): Weight vector for the logistic regression model.
        bias (float): Bias term.
        loss_history (list): List of loss values at each iteration for plotting.
    """

    def __init__(self, lr=0.001, n_iters=1000):
        """
        Initialize the logistic regression model.

        Args:
            lr (float): Learning rate. Default is 0.001.
            n_iters (int): Number of training iterations. Default is 1000.
        """
        self.lr = lr
        self.it = n_iters
        self.weights: np.ndarray = np.array([])
        self.bias: float | None = None
        self.loss_history = []

    def fit(self, X, y):
        """
        Train the logistic regression model using gradient descent.

        Args:
            X (np.ndarray): Training data of shape (n_samples, n_features).
            y (np.ndarray): Target labels of shape (n_samples,).
        """
        # Initialize weights and bias
        n_samples, n_features = X.shape
        self.weights = np.zeros(n_features)
        self.bias = 0

        for _ in range(self.it):
            linear_model = np.dot(X, self.weights) + self.bias
            y_predicted = self._sigmoid(linear_model)

            # Binary cross-entropy loss
            loss = -np.mean(
                y * np.log(y_predicted + 1e-15)
                + (1 - y) * np.log(1 - y_predicted + 1e-15)
            )
            self.loss_history.append(loss)

            # Gradients
            dw = (1 / n_samples) * np.dot(X.T, y_predicted - y)
            db = (1 / n_samples) * np.sum(y_predicted - y)

            # Update parameters
            self.weights -= self.lr * dw
            self.bias -= self.lr * db

    def predict(self, X):
        """
        Predict binary labels for input data.

        Args:
            X (np.ndarray): Input data of shape (n_samples, n_features).

        Returns:
            list[int]: Predicted labels (0 or 1) for each sample.
        """
        linear_model = np.dot(X, self.weights) + self.bias
        y_predicted = self._sigmoid(linear_model)
        y_predicted_cls = [1 if i > 0.5 else 0 for i in y_predicted]
        return y_predicted_cls

    def _sigmoid(self, z):
        """
        Sigmoid activation function with overflow protection.

        Args:
            z (np.ndarray): Input array.

        Returns:
            np.ndarray: Output after applying sigmoid function.
        """
        z = np.clip(z, -500, 500)
        return 1 / (1 + np.exp(-z))
