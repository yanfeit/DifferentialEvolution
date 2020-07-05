import matplotlib.pyplot as plt 
import numpy as np 
import pandas as pd 

filenames = ['d8.csv','d16.csv','d32.csv','d64.csv','d128.csv','d256.csv']
legends = [8, 16, 32, 64, 128, 256]

for i, filename in enumerate(filenames):
	res = pd.read_csv(filename)
	data = res.values
	plt.plot(data[:, 0], data[:, 1], label = r'$d$ = {0}'.format(legends[i]))

plt.xlabel("Iteration No.", fontsize = 16)
plt.ylabel(r"$f(\mathbf{x})$", fontsize = 32)
plt.legend(loc = 'upper right')
plt.tight_layout()
plt.savefig("convergence_f_n.pdf")
plt.show()





