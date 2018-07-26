#!/usr/bin/env python

import re

class KeymapConverter:

  def __init__(self, filename):
    self.filename = filename

  def read_keymaps(self):
    with open(self.filename) as f:
      lines = f.readlines()

    mode = 0
    for line in lines:
      line = line[:-1]
      if mode == 0:
        if "KC_KEYMAP" in line:
          matches = re.match(r'.*\[(.*)\] = .*', line)
          if matches:
            layer_name = matches.group(1)
            layer_name = layer_name[1:].capitalize()
            print '###', layer_name
            print '```'
          mode = 1
      elif mode == 1:
        if "//" in line:
          print line[4:]
        elif ")" in line:
          mode = 0
          print '```'
          print
        elif line[-1] == ',':
          print "|" + line[5:-1] + "|"
        else:
          print "|" + line[5:] + "|"

converter = KeymapConverter('keymap.c')
converter.read_keymaps()
