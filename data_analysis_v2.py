import numpy as np
import matplotlib.pyplot as plt

def load_data(velocities, folder="N=5000, vel=0.01, k_alpha=4, vd=2"):
    r_infi_list = []
    y_error = []

    for vel in velocities:
        file = "{:.6f}".format(vel)
        DIR_PATH = f"data/{folder}/evolution_{file}.txt"
        data = np.loadtxt(DIR_PATH)

        r_infi = data[:, 0]
        r_infi_list.append(r_infi.mean())
        y_error.append(r_infi.std())

    return np.array(r_infi_list), np.array(y_error)

def plot_histograms(velocities, bins, folder):
    for vel in velocities:
        file = "{:.6f}".format(vel)
        DIR_PATH = f"data/{folder}/evolution_{file}.txt"
        data = np.loadtxt(DIR_PATH)

        r_infi = data[:, 0]
        plt.hist(r_infi, bins=bins, edgecolor='black', alpha=0.5, label=round(vel, 3))
        plt.legend()
        plt.show()

def main(filename="power_law_5k_alpha_4", folder="N=5000, vel=0.01, k_alpha=4, vd=2"):
    velocities = np.arange(0.01, 0.05, 0.005)
    bins = np.arange(0, 5000, 100)

    r_infi_list, y_error = load_data(velocities)
    np.save(filename, r_infi_list)
    np.save(f"velocities_{filename}", velocities)

    plt.plot(velocities, r_infi_list / 5000)
    plt.scatter(velocities, r_infi_list / 5000)
    #plt.errorbar(velocities, r_infi_list / 5000 , yerr=y_error / 5000, fmt='o', capsize=5)
    plt.show()

    #plot_histograms(velocities, bins, folder)

if __name__ == "__main__":
    main("power_law_5k_alpha=4")