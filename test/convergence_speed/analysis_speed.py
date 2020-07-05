import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# dim 16  take 0.401588 seconds to execute per time
# dim 32  take 1.501346 seconds to execute per time
# dim 64  take 5.951431 seconds to execute per time
# dim 128 take 23.950499 seconds to execute per time
# dim 256 take 100.562294 seconds to execute per time

dims = [16, 32, 64, 128, 256]
time_t = [0.401588, 1.501346, 5.951431, 23.950499, 100.562294]

x = np.arange(len(dims))  # the label locations

rects = plt.bar(x, time_t, align = 'center', alpha = 0.7)

for rect in rects:
    height = rect.get_height()
    plt.annotate('{}'.format(height), xy=(rect.get_x() + rect.get_width()/2, height),
                xytext = (0, 3),
                textcoords = 'offset points',
                ha = 'center', 
                va = 'bottom')

plt.xlabel("Dimension " + r"$d$", fontsize = 16)
plt.ylabel("Time Costed(s)", fontsize = 16)
plt.title(r"$t \sim O(d^2)$", fontsize = 16)
plt.xticks(x, dims)

plt.tight_layout()
plt.savefig("convergence_speed.pdf")
plt.show()


