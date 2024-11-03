import matplotlib.pyplot as plt
import numpy as np
import sys

from matplotlib.patches import Ellipse

ellipses = np.loadtxt("ellipses.txt", dtype=[
    ("x", int), ("y", int), 
    ("mayor", float), ("minor", float), 
    ("angle", float)
])

fig, ax = plt.subplots()
ax.set(xlim=(0, 255), ylim=(255, 0), aspect="equal")
for ellipse in ellipses:
    viewed_ellipse = Ellipse((ellipse["x"], ellipse["y"]), ellipse["mayor"] * 2, ellipse["minor"] * 2, angle=ellipse["angle"], alpha = 1)
    ax.add_artist(
        viewed_ellipse
    )

    viewed_ellipse.set_facecolor("w")
    viewed_ellipse.set_edgecolor("k")
    

plt.show()

