class LinearRegression:
    def __init__(self, weight=0.0, bias=0.0):
        self.weight = weight
        self.bias = bias

    def predict(self, x):
        return self.weight * x + self.bias

    def fit(self, sepal_length, sepal_width, lr=0.01, iters=100):
        self.weight, self.bias, loss_history = training(
            sepal_length, sepal_width, self.weight, self.bias, lr, iters
        )
        return loss_history


def loss_function(sepal_length, sepal_width, weight, bias):
    total_error = 0.0
    for i in range(len(sepal_length)):
        prediction = weight * sepal_length[i] + bias
        total_error += (sepal_width[i] - prediction) ** 2
    return total_error / len(sepal_length)


def update_weights(sepal_length, sepal_width, weight, bias, lr):
    weight_deriv = 0.0
    bias_deriv = 0.0
    n = len(sepal_length)

    for i in range(n):
        prediction = weight * sepal_length[i] + bias
        error = sepal_width[i] - prediction
        weight_deriv += -2 * sepal_length[i] * error
        bias_deriv += -2 * error

    weight -= lr * (weight_deriv / n)
    bias -= lr * (bias_deriv / n)

    return weight, bias


def training(sepal_length, sepal_width, weight, bias, lr, iters):
    loss_history = []

    for _ in range(iters):
        weight, bias = update_weights(sepal_length, sepal_width, weight, bias, lr)
        loss = loss_function(sepal_length, sepal_width, weight, bias)
        loss_history.append(loss)

    return weight, bias, loss_history
