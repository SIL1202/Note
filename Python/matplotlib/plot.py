from matplotlib import pyplot as plt

# style
plt.style.use("dark_background")

# set the data
x_1 = [i for i in range(1, 100, 5)]
y_1 = [i * i for i in x_1]
y_2 = [i * -i for i in x_1]

# if figure object doesn't exist, create a figure object
# plot
plt.plot(x_1, y_1, label="positive")
plt.plot(x_1, y_2, label="nagetive")

plt.xlabel("x")
plt.ylabel("y")

plt.title("exponential")
plt.legend()
plt.tight_layout()  # Typographic remediation
# plt.grid(True)
plt.show()

# ----------------------------------------------------------------------------------
# Use the .figure() method to create a canvas, draw different charts, or make more detailed settings for the figure.
#
# f = plt.figure()
# plt.subplot()
# plt.plot(x)
# plt.show()
#
# plt.get_backend()
