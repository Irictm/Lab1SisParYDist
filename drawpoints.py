import matplotlib.pyplot as plt
import numpy as np
from matplotlib.patches import Ellipse

points = np.loadtxt("scatter.txt", dtype=[
    ("x", int), ("y", int)
])
ellipses = np.loadtxt("ellipses.txt", dtype=[
    ("x", int), ("y", int), 
    ("mayor", float), ("minor", float), 
    ("angle", float)
])

heatmap, xedges, yedges = np.histogram2d(ellipses["x"], ellipses["y"], bins=100)

fig, ax = plt.subplots()
ax.set(xlim=(0, 255), ylim=(255, 0), aspect="equal")
plt.imshow(heatmap.T, origin="lower", aspect="auto", extent=[xedges[0], xedges[-1], yedges[0], yedges[-1]], cmap="hot")

for ellipse in ellipses:
    viewed_ellipse = Ellipse((ellipse["x"], ellipse["y"]), ellipse["mayor"] * 2, ellipse["minor"] * 2, angle=ellipse["angle"], alpha = 0.2)
    ax.add_artist(
        viewed_ellipse
    )

    viewed_ellipse.set_facecolor("w")
    viewed_ellipse.set_edgecolor("k")

plt.scatter(points["x"], points["y"])
plt.show()

