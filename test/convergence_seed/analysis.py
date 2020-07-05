import matplotlib.pyplot as plt 
import numpy as np 
import pandas as pd 

strategy = 2

filenames = ['seed3dim16.csv','seed5dim16.csv','seed7dim16.csv', \
			 'seed9dim16.csv','seed11dim16.csv']

for i in range(len(filenames)):
	filenames[i] = 'strategy{}'.format(strategy) + filenames[i]

seeds = [3, 5, 7, 9, 11]

for i, filename in enumerate(filenames):
	res = pd.read_csv(filename)
	data = res.values
	plt.plot(data[:, 0], data[:, 1], label = r'seed = {0}'.format(seeds[i]))

plt.title("Strategy: DE/rand/1/bin, Dimension 16", fontsize = 16)
plt.xlabel("Iteration No.", fontsize = 16)
plt.ylabel(r"$f(\mathbf{x})$", fontsize = 32)
plt.legend(loc = 'upper right')
plt.tight_layout()
plt.savefig("convergence_seed_strategy{0}.pdf".format(strategy))
plt.show()