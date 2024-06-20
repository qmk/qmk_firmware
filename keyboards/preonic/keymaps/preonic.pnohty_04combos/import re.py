#  %%
# write a python script that 
# given a file at 
# file_path = r'C:\Users\scout\Documents\kb\.build_qmk\keyboards\preonic\keymaps\preonic.pnohty_04combos\.layout.c'
# read only those line beginning with "const uint16_t PROGMEM ly", 
# read them in from position six to the left of the first square bracket, discarding all characters before that
# read only lines that have the form ly(layer_number)_(row_number)={keycodes} where layer and row number are single digit integers
# return a nested  list of the form [[layer_name, row_number, [keycodes]]]

# %%
import re

#  %%
# Define the path to the file
file_root = r'C:\Users\scout\Documents\kb\.build_qmk\keyboards'
file_proj = r'\preonic\keymaps\preonic.pnohty_04combos\.layout.c'

file_path = file_root + file_proj
var_first = 'const uint16_t PROGMEM ly'

# %%
def extr_ll(file_path):
  layer_line_array = []
  with open(file_path, 'r') as file:
    lines = file.readlines()
    ll = [line for line in lines[:30] if line.startswith(var_first)]
  for line in ll:
    list_name = re.search(r'ly\d+_r\d+', line)
    if list_name:
      list_name = list_name.group()
    # xtart_index = line.find('[') - 6
    #   if start_index >= 0:
    #     layer_name = line[start_index+2:start_index+3]
    #     row_number = line[start_index+5]
      layer_name, row_name = list_name.split('_')
      keycodes = re.findall(r'{(.*?)}', line)
      if keycodes:
        layer_line_array.append((layer_name, row_name, 
                      [code.strip().replace('KC_', '').replace('NO', ' ') 
                       for code in keycodes[0].split(',')]))
  return layer_line_array

ll = extr_ll(file_path)
print(*ll, sep='\n')

# %%

# i want a rowname [keycodes by layer] for each row, where the keycodes are separated by commas
# and surrounded by double quotes like this
# r0 = ["ly0 r0[0] \n ly3r0[0] \n ly1r0[0] \n  ly2r0[0]", "ly0r0[1]\n ly3r0[1] \n ly1r0[1] \n ly2r0[1]", ...  ]
# ...
# r3 = ["ly0r3[0] \n ly3r3[0] \n ly1r3[0] \n ly2r3[0]", "ly0r3[1] \n ly3r3[1] \n ly1r3[1] \n ly2r3[1]", ...  ]
print(ll[1][2][2])


# %%

def format_layout(nested_list):
  formatted_layout = []
  for row in lxc_z:
    row_name = row[1]
    layer_keycodes = []
    for layer in row[2]:
      layer_keycodes.append([{row[0]}][{row[1]}][{layer}])
    formatted_layout.append("hi")
  return formatted_layout

formatted_layout = format_layout(ll)
print(*formatted_layout, sep='\n')



# %%
# Initialize an empty dictionary to store the lists for each unique row name
rows_dict = {}

# Iterate over the ll list
for layer_name, row_name, keycodes in ll:
  # Concatenate the keycodes with a "." separator
  keycodes_str = ".".join(keycodes)
  
  # Check if the row name is already a key in the dictionary
  if row_name in rows_dict:
    # If it is, append the concatenated keycodes to the corresponding list
    rows_dict[row_name].append(keycodes_str)
  else:
    # If it is not, create a new list for that row name and add the concatenated keycodes to it
    rows_dict[row_name] = [keycodes_str]

# Print the dictionary
for row_name, keycodes in rows_dict.items():
  print(f"{row_name}_all_lyrs: {keycodes}")
# %%
