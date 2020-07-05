import matplotlib.pyplot as plt 
import numpy as np 
import pandas as pd 

strategy = 5

filenames = ['mut5crossp3.csv','mut5crossp7.csv','mut7crossp3.csv', \
			 'mut7crossp7.csv','mut9crossp3.csv','mut9crossp7.csv']

for i in range(len(filenames)):
	filenames[i] = 'strategy{}'.format(strategy) + filenames[i]

print(filenames)

muts = [0.5, 0.5, 0.7, 0.7, 0.9, 0.9]
crossp = [0.3, 0.7, 0.3, 0.7, 0.3, 0.7]

for i, filename in enumerate(filenames):
	res = pd.read_csv(filename)
	data = res.values
	plt.plot(data[:, 0], data[:, 1], label = r'mut = {0}, crossp = {1}'.format(muts[i], crossp[i]))

plt.title("Strategy: DE/rand/2/bin", fontsize = 16)
plt.xlabel("Iteration No.", fontsize = 16)
plt.ylabel(r"$f(\mathbf{x})$", fontsize = 32)
plt.legend(loc = 'upper right')
plt.tight_layout()
plt.savefig("convergence_params_strategy{0}.pdf".format(strategy))
plt.show()