import matplotlib.pyplot as plt
import numpy as np
from sklearn import datasets
from linear_regression import LinearRegression as LR, loss_function

iris: "datasets.Bunch" = datasets.load_iris()
X = iris.data[:, 0]  # Sepal Length
y = iris.data[:, 3]  # Petal Width

model = LR()
loss_function = model.fit(X, y, lr=0.01, iters=500)

print(f"Final weight: {model.weight}, Final bias: {model.bias}")
print(f"Final loss: {loss_function[-1]}")
print(f"predict patal width: {model.predict(4.5)}")

# draw the learning curve
plt.plot(range(len(loss_function)), loss_function, color="purple")
plt.title("Loss over iterations")
plt.xlabel("Iteration")
plt.ylabel("Loss")
plt.grid(True)
plt.show()

# draw scatter information
plt.scatter(X, y, color="blue", label="data points")

x_line = np.linspace(min(X), max(X), 100)
# give the Sepal Length and predict the Petal Width
y_line = model.predict(x_line)

plt.plot(x_line, y_line, color="red", label="regression line")

plt.title("Sepal Length vs Petal Width")
plt.xlabel("Sepal Length")
plt.ylabel("Petal Width")
plt.legend()
plt.grid(True)
plt.show()
