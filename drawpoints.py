import matplotlib.pyplot as plt
import numpy as np

points = np.loadtxt("scatter.txt", dtype=[
    ("x", int), ("y", int)
])

plt.scatter(points["x"], points["y"])
plt.show()

