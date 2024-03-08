import os
import shutil
import re

# Read the simulation.txt file
file_path = 'data/simulation_data.txt'  # Adjust the path accordingly
with open(file_path, 'r') as file:
    content = file.read()

# Find the seed number using regex
seed_match = re.search(r'seed\s*=\s*(\d+)', content)
N_match = re.search(r'N\s*=\s*(\d+)', content)
tau_match = re.search(r'tau Rotation \s*=\s*(\d+)', content)
vel_match = re.search(r'active_vel \s*=\s*(\d+).(\d+)', content)
tau_t_match = re.search(r'tau_t \s*=\s*(\d+)', content)
vel_dist = re.search(r'Vel Distribut\s*=\s*(\d+)', content)

if seed_match:
    seed_number = seed_match.group(1)
    N_number = N_match.group(1)
    tau_number = tau_match.group(1)
    vel_head = vel_match.group(1)
    vel_tail = vel_match.group(2)
    tau_t_number = tau_t_match.group(1)
    vel_dist = vel_dist.group(1)

    new_folder_name = f'data/N={N_number}, vel={vel_head}.{vel_tail}, k_alpha=8, vd={vel_dist}'  # Folder name based on the seed number
    
    # Create a directory with the name of the seed if it doesn't exist
    if not os.path.exists(new_folder_name):
        os.makedirs(new_folder_name)
    
    # Move all .txt files to the new folder
    txt_files = [f for f in os.listdir('data') if f.endswith('.txt') or f.endswith('.png')]
    for txt_file in txt_files:
        shutil.move(os.path.join('data', txt_file), new_folder_name)