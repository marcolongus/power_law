import numpy as np
import matplotlib.pyplot as plt

def power_law(x, x_min, gamma):
	result = ((gamma-1)/x_min)  * np.power(x / x_min, -gamma)
	return result

def exponential(x, x_mean):
	result = (1 / x_mean)  * np.exp(-x / x_mean)
	return result

DIR_PATH = "data/velocites_data.txt"

data = np.loadtxt(DIR_PATH, usecols=0)

velocities = np.arange(0.01, 0.1, 0.005)
gamma = 4
print(velocities)
bins = np.arange(0, 0.3, 0.01)

for i in range(0, 18, 1):
	left_limit = i * 1000
	right_limit = (i + 1) * 1000
	print(left_limit, right_limit)
	print("v_mean_sample: ", data[i * 1000:(i + 1) * 1000].mean())
	print()

	v_min = velocities[i] * (gamma - 2) / (gamma -1)
	
	v = np.arange(v_min, data[left_limit:right_limit].max(), 0.001)
	plt.xlim(v_min - 0.001, data[left_limit:right_limit].max() + 0.001)
	plt.plot(v, power_law(v, v_min, gamma))


	plt.hist(data[left_limit:right_limit], bins=bins, edgecolor="black", linestyle="dashed", label=i, alpha=0.7, density=True)
	plt.loglog()
	plt.legend()
	plt.show()