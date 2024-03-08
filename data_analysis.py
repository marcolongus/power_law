import numpy as np
import matplotlib.pyplot as plt

DIR_PATH = "data/N=1000, vel=0.01, k_alpha=4, vd=2/evolution.txt"

velocities = np.arange(0.01, 0.1, 0.005)

r_infi_list = []
bins = np.arange(0, 1000, 20)
y_error = []  # Error values
for vel in velocities:
    file = "{:.6f}".format(vel)
    DIR_PATH = f"data/N=1000, vel=0.01, k_alpha=5, vd=2/evolution_{file}.txt"
    DIR_PATH = f"data/evolution_{file}.txt"
    data = np.loadtxt(DIR_PATH)

    r_infi = data[:, 0]
    plt.hist(r_infi, bins=bins, edgecolor="black", alpha=0.5, label=round(vel,3))
    #plt.loglog()
    plt.legend()
    plt.show()

    print(r_infi.mean())
    r_infi_list.append(r_infi.mean())
    y_error.append(r_infi.std())

print(y_error)

r_infi_list = np.array(r_infi_list)

k_alpha = 5
np.save(f"power_law_alpha={k_alpha}", r_infi_list)
np.save(f"velocities_power_law_alpha={k_alpha}", velocities)
plt.plot(velocities, r_infi_list / 1000)
plt.scatter(velocities, r_infi_list / 1000)
# plt.errorbar(velocities, r_infi_list / 1000 , yerr=np.array(y_error)/1000, fmt='o', capsize=5)

plt.show()


dt = 0.05
v = 4
print(dt * v)
