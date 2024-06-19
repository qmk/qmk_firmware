import re
#  %%
# Define the path to the file
file_path = 'preonic.pnohty_04combos\\.layout.c'
import re
def read_keycodes(file_path):
  with open(file_path, 'r') as file:
    keycodes = [code.strip() for line in file.readlines()[:30] if not line.startswith('//') for code in re.findall(r'{(.*?)}', line)]
  return keycodes

# Read keycodes from the file
keycodes = read_keycodes(file_path)

# %%
def print_simplified_matrix(keycodes):
    # Format the keycodes into rows
    matrix = []
    row = []
    for i, keycode in enumerate(keycodes):
        row.append(f'"{keycode}"')
        if (i + 1) % 12 == 0:  # Assuming 12 keycodes per row for simplicity
            matrix.append(f"[{', '.join(row)}]")
            row = []
    if row:
        matrix.append(f"[{', '.join(row)}]")  # Append the last row if it's incomplete
    
    # Print the formatted matrix
    for row in matrix:
        print(row)


# Print the simplified matrix
print_simplified_matrix(keycodes)

# %%
