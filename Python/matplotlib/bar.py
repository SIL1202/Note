from matplotlib import pyplot as plt
import numpy as np

plt.style.use("dark_background")
dev_y = [38496, 42000, 46752, 49320, 53200, 56000, 62316, 64928, 67317, 68748, 73752]
py_dev_y = [45372, 48876, 53850, 57287, 63016, 65998, 70003, 70000, 71496, 75370, 83640]
js_dev_y = [
    37810,
    43515,
    46823,
    49293,
    53437,
    56373,
    62375,
    66674,
    68745,
    68746,
    745831,
]

width = 0.25
x_indexes = np.arange(len(dev_y))
indexes = [range(len(dev_y))]
plt.bar(x_indexes - width, dev_y, color="#2C3030", label="All Devs")
plt.bar(x_indexes, py_dev_y, color="#008fd5", label="Python")
plt.bar(x_indexes + width, js_dev_y, color="#e5ae38", label="JavaScript")

plt.show()
