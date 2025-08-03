import numpy as np
import matplotlib.pyplot as plt


def sigmoid(z: np.ndarray) -> np.ndarray:
    """
    Compute the sigmoid of z.

    The sigmoid function maps any real-valued number to the range (0, 1).
    It is defined as: sigmoid(z) = 1 / (1 + exp(-z))

    Args:
        z (np.ndarray): Input array or scalar.

    Returns:
        np.ndarray: Output array where sigmoid is applied element-wise.
    """
    # Clip values to prevent overflow in exp()
    z = np.clip(z, -500, 500)
    return 1 / (1 + np.exp(-z))


# Generate an array of values from -10 to 10 to simulate linear model output z = wx + b
z = np.linspace(-10, 10, 200)

# Apply sigmoid function to each value
sig = sigmoid(z)

# Plot the sigmoid curve
plt.plot(z, sig)
plt.title("Sigmoid Function")
plt.xlabel("z (linear output)")
plt.ylabel("sigmoid(z)")
plt.grid(True)
plt.show()
