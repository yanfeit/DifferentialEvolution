import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

strategy = ['DE/best/1/bin',
            'DE/rand/1/bin',
            'DE/rand-to-best/1/bin',
            'DE/best/2/bin',
            'DE/rand/2/bin']

filenames = ['strategy1Ackley.csv', 'strategy2Ackley.csv', 'strategy3Ackley.csv',
             'strategy4Ackley.csv', 'strategy5Ackley.csv']

for i, filename in enumerate(filenames):
    res = pd.read_csv(filename)
    data = res.values
    plt.plot(data[:, 0], data[:, 1], label=r'strategy = {0}'.format(strategy[i]))

plt.title("Ackley Func., Dimension 64", fontsize=16)
plt.xlabel("Iteration No.", fontsize=16)
plt.ylabel(r"$f(\mathbf{x})$", fontsize=32)
plt.legend(loc='upper right')
plt.tight_layout()
plt.savefig("convergence_strategy_Ackley.pdf".format(strategy))
plt.show()
