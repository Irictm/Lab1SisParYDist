import matplotlib.pyplot as plt
import numpy as np
import sys

from matplotlib.patches import Ellipse

elipses = np.loadtxt("elipses.txt", dtype=[
    ("x", int), ("y", int), 
    ("mayor", float), ("minor", float), 
    ("angle", float)
])

fig, ax = plt.subplots()
ax.set(xlim=(0, 255), ylim=(255, 0), aspect="equal")
for elipse in elipses:
    viewed_ellipse = Ellipse((elipse["x"], elipse["y"]), elipse["mayor"] * 2, elipse["minor"] * 2, angle=elipse["angle"], alpha = 1)
    ax.add_artist(
        viewed_ellipse
    )

    viewed_ellipse.set_facecolor("w")
    viewed_ellipse.set_edgecolor("k")
    

plt.show()

