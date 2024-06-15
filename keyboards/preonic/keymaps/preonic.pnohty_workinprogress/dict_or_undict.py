import re

path_root     = r'C:\Users\scout\Documents\keeb\.build_qmk\keyboards\preonic\keymaps\preonic_adb'
file_kmp      = r'\keymap.c'
file_kmp_def  = r'\keycodes.h'
path_kmp      = path_root + file_kmp
path_kmp_def  = path_root + file_kmp_def

def dict_do_un(path_to_def, do_d=True):
  key_index, value_index = (2, 1) if do_d else (1, 2)
  with open(path_to_def, 'r') as dfs_file:
    dict_or_un = {line.split()[key_index]: line.split()[value_index] for line in dfs_file if line.startswith("#define")}
  return dict_or_un

def file_subword(file_path, dictionary):
  with open(file_path, 'r') as file: content = file.read()
  pattern = re.compile(r'\b(' + '|'.join(re.escape(key) for key in dictionary.keys()) + r')\b')
  updated_content = pattern.sub(lambda match: dictionary[match.group(0)], content)
  with open(file_path, 'w') as file: file.write(updated_content)

def do_dict(): file_subword(path_kmp, dict_do_un(path_kmp_def, do_d=True))

def un_dict(): file_subword(path_kmp, dict_do_un(path_kmp_def, do_d=False))

un_dict()
