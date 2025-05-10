import os

# Get the absolute path of the script
script_dir = os.path.dirname(os.path.abspath(__file__))
file_path = os.path.join(script_dir, "empty_file.txt")

with open(file_path, "w") as file:
    pass