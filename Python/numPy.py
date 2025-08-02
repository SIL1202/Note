import numpy as np

arr1 = np.array([1, 2, 3, 4, 5])
arr2 = np.array([6, 7, 8, 9, 10])

number = 10
print(f"Add a value for arr1: {arr1 + number}")  # arr1 + number
print(f"Time a value for arr2: {arr1 * number}")  # arr1 * number
print(f"Sum of two arrays: {arr1 + arr2}")  # arr1 + arr2
print(f"Dot product of two arrays: {arr1 @ arr2}")  # arr1 @ arr2
print(f"Mean of arr2: {np.mean(arr2)}")  # np.mean(arr2)

print(
    f"Create a 2x3 matrix and all the elements are zero:\n {np.zeros((2, 3))}"
)  # np.zeros((2, 3))
# np.ones((2, 3))

print(f"Create uniform array: {np.arange(0, 10, 2)}")  # np.arange(0, 10, 2)
print(f"Create uniform array: {np.linspace(0, 10, 5)}")  # np.linspace(0, 10, 5)
print(
    f"Create a 2x3 matrix and full with number:\n {np.full((2, 3), number)}"
)  # np.full((2, 3), number)

print(f"Create a unit matrix:\n {np.eye(number//2)}")  # np.eye(number//2)
print(
    f"Create a random matrix:\n {np.random.random((2, 3))}"
)  # np.random.random((2, 3))
