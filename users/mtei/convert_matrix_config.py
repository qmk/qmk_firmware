#!/usr/bin/env python3

# Copyright 2022 Takeshi Ishii (@mtei)
# Copyright 2022 Ein Terakawa (a_p_u_r_o@elfmimi)
# SPDX-License-Identifier: GPL-2.0-or-later

import sys
import re
import json
import subprocess

if len(sys.argv) != 2:
  print(f"usage: python3 {sys.argv[0]} <config_file or info.json>")
  exit(1)

col_pins = None
col_pins_right = None
col_pins_ext = None
col_pins_ext_right = None
row_pins = None
row_pins_right = None
row_pins_ext = None
row_pins_ext_right = None

input_port_pin = None
output_port_pin = None
input_port_pin_right = None
output_port_pin_right = None

def main():
  read_configuration(sys.argv[1])
  build_all_port_pin_lists()
  print_all_port_pin_lists()

def read_configuration(file):
  if re.match('^.*info.json', file):
    read_configuration_from_info_json(file)
  else:
    read_configuration_from_config_h(file)

def build_all_port_pin_lists():
  global input_port_pin, output_port_pin, input_port_pin_right, output_port_pin_right
  input_port_pin = build_port_pin_list(col_pins) if col_pins else input_port_pin
  # p input_port_pin
  input_port_pin = build_port_pin_list_ext(col_pins_ext) if col_pins_ext else input_port_pin
  # p input_port_pin

  output_port_pin = build_port_pin_list(row_pins) if row_pins else output_port_pin
  # p output_port_pin
  output_port_pin = build_port_pin_list_ext(row_pins_ext) if row_pins_ext else output_port_pin
  # p output_port_pin

  input_port_pin_right = build_port_pin_list(col_pins_right) if col_pins_right else input_port_pin_right
  # p input_port_pin_right
  input_port_pin_right = build_port_pin_list_ext(col_pins_ext_right) if col_pins_ext_right else input_port_pin_right
  # p input_port_pin_right

  output_port_pin_right = build_port_pin_list(row_pins_right) if row_pins_right else output_port_pin_right
  # p output_port_pin_right
  output_port_pin_right = build_port_pin_list_ext(row_pins_ext_right) if row_pins_ext_right else output_port_pin_right
  # p output_port_pin_right

def print_all_port_pin_lists():
  print("#pragma once")

  if input_port_pin:
    if col_pins_ext:
      print(f" /* #define EXTENDED_MATRIX_COL_PINS {col_pins_ext} */")
    else:
      print(f" /* #define MATRIX_COL_PINS {{{col_pins}}} */")
      print("#undef MATRIX_COL_PINS")

    print("#define SWITCH_MATRIX_INPUT_0 \\")
    print_port(input_port_pin[0])
    print_pin(input_port_pin[1], True)
    print("")

  if output_port_pin:
    if row_pins_ext:
      print(f" /* #define EXTENDED_MATRIX_ROW_PINS {row_pins_ext} */")
    else:
      print(f" /* #define MATRIX_ROW_PINS {{{row_pins}}} */")
      print("#undef MATRIX_ROW_PINS")

    print("#define SWITCH_MATRIX_OUTPUT_0 \\")
    print_port(output_port_pin[0])
    print_pin(output_port_pin[1])
    print("")

  if input_port_pin_right:
    if col_pins_ext_right:
      print(f" /* #define EXTENDED_MATRIX_COL_PINS_RIGHT {{{col_pins_ext_right}}} */")
    else:
      print(f" /* #define MATRIX_COL_PINS_RIGHT {{{col_pins_right}}} */")
      print("#undef MATRIX_COL_PINS_RIGHT")

    print("#define SWITCH_MATRIX_INPUT_1 \\")
    print_port(input_port_pin_right[0])
    print_pin(input_port_pin_right[1], True)
    print("")

  if output_port_pin_right:
    if row_pins_ext_right:
      print(f" /* #define EXTENDED_MATRIX_ROW_PINS_RIGHT {row_pins_ext_right} */")
    else:
      print(f" /* #define MATRIX_ROW_PINS_RIGHT {{{row_pins_right}}} */")
      print("#undef MATRIX_ROW_PINS_RIGHT")

    print("#define SWITCH_MATRIX_OUTPUT_1 \\")
    print_port(output_port_pin_right[0])
    print_pin(output_port_pin_right[1])
    print("")

def read_configuration_from_config_h(file):
  global col_pins, col_pins_right, col_pins_ext, col_pins_ext_right
  global row_pins, row_pins_right, row_pins_ext, row_pins_ext_right
  gcc = "gcc"
  conf = []
  with subprocess.Popen([gcc, "-dM", "-E", "-xc", file], stdout=subprocess.PIPE) as p:
    for line in p.stdout:
      if b"define MATRIX_" in line or b"define EXTENDED_MATRIX_" in line:
        conf.append(line.rstrip().decode())
  for c in conf:
    m = re.match('^[ \t]*#[ \t]*define[ \t]* MATRIX_COL_PINS[ \t]+{(.*)}', c)
    col_pins = m[1] if m else col_pins
    m = re.match('^[ \t]*#[ \t]*define[ \t]* MATRIX_COL_PINS_RIGHT[ \t]+{(.*)}', c)
    col_pins_right = m[1] if m else col_pins_right
    m = re.match('^[ \t]*#[ \t]*define[ \t]* EXTENDED_MATRIX_COL_PINS[ \t]+(.*)', c)
    col_pins_ext = m[1] if m else col_pins_ext
    m = re.match('^[ \t]*#[ \t]*define[ \t]* EXTENDED_MATRIX_COL_PINS_RIGHT[ \t]+(.*)', c)
    col_pins_ext_right = m[1] if m else col_pins_ext_right
    m = re.match('^[ \t]*#[ \t]*define[ \t]* MATRIX_ROW_PINS[ \t]+{(.*)}', c)
    row_pins = m[1] if m else row_pins
    m = re.match('^[ \t]*#[ \t]*define[ \t]* MATRIX_ROW_PINS_RIGHT[ \t]+{(.*)}', c)
    row_pins_right = m[1] if m else row_pins_right
    m = re.match('^[ \t]*#[ \t]*define[ \t]* EXTENDED_MATRIX_ROW_PINS[ \t]+(.*)', c)
    row_pins_ext = m[1] if m else row_pins_ext
    m = re.match('^[ \t]*#[ \t]*define[ \t]* EXTENDED_MATRIX_ROW_PINS_RIGHT[ \t]+(.*)', c)
    row_pins_ext_right = m[1] if m else row_pins_ext_right

def read_configuration_from_info_json(file):
  global col_pins, row_pins
  with open(file) as f:
    info = json.load(f)
  if "matrix_pins" in info:
    col_pins = ",".join(info["matrix_pins"]["cols"])
    row_pins = ",".join(info["matrix_pins"]["rows"])
  else:
    print(f"ERROR: {file} does not contain matrix_pins information.")
    exit(1)

def build_port_pin_list(pins):
  # p pins
  #    if source data is '#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 }'
  # example: pins = " F4, F5, F6, F7, B1, B3, B2 "
  pin_number = 0
  raw_list = []
  for pin in [pin.strip() for pin in pins.split(",")]:
    pin_number += 1
    if pin == "NO_PIN":
      port = "NO_PIN"
      mask = 0
      raw_list.append(["NO_DEVICE", port, mask, 0])
    else:
      m = re.match('([A-Z]+)([0-9]*)', pin)
      port = m[1]+"0"
      mask = (1<<int(m[2]))
      raw_list.append(["MCU_GPIO", port, mask, (1<<(pin_number - 1))])
  # p raw_list
  # example: raw_list = [["MCU_GPIO", "F0", 16, 1], ["MCU_GPIO", "F0", 32, 2], ["MCU_GPIO", "F0", 64, 4], ["MCU_GPIO", "F0", 128, 8], ["MCU_GPIO", "B0", 2, 16], ["MCU_GPIO", "B0", 8, 32], ["MCU_GPIO", "B0", 4, 64]]
  return build_port_pin_list_sub(raw_list)

def build_port_pin_list_ext(pins):
  # p pins
  #   if source data is
  #      '#define EXTENDED_MATRIX_COL_PINS \
  #          (MCU_GPIO, F0, 4), (MCU_GPIO, F0,5 ), (MCU_GPIO, F0,6 ), \
  #          (MCU_GPIO, F0, 7), (MCU_GPIO, B0, 1), (MCU_GPIO, B0, 3), (MCU_GPIO, B0, 2)'
  # example: pins = "(MCU_GPIO, F0, 4), (MCU_GPIO, F0,5 ), (MCU_GPIO, F0,6 ), (MCU_GPIO, F0, 7), (MCU_GPIO, B0, 1), (MCU_GPIO, B0, 3), (MCU_GPIO, B0, 2)"
  pin_number = 0
  raw_list = []
  sepalate_pins = re.split('\s*\)\s*,\s*\(\s*', re.sub('^\s*\(\s*|\s*\)\s*$', '', pins))
  for pin in sepalate_pins:
    pin = re.split('\s*,\s*', pin)
    dev = pin[0]
    port = pin[1]
    pin_number += 1
    if dev == "NO_DEVICE" or port == "NO_PIN":
      raw_list.append(["NO_DEVICE", "NO_PIN", 0, 0])
    else:
      mask = (1<<int(pin[2]))
      raw_list.append([dev, port, mask, (1<<(pin_number - 1))])
  # p raw_list
  # example: raw_list = [["MCU_GPIO", "F0", 16, 1], ["MCU_GPIO", "F0", 32, 2], ["MCU_GPIO", "F0", 64, 4], ["MCU_GPIO", "F0", 128, 8], ["MCU_GPIO", "B0", 2, 16], ["MCU_GPIO", "B0", 8, 32], ["MCU_GPIO", "B0", 4, 64]]
  return build_port_pin_list_sub(raw_list)

def build_port_pin_list_sub(raw_list):
  #### build ports list ####
  port_num = 0
  ports = {}
  for pin in raw_list:
    key = tuple(pin[0:2])
    if key != tuple(["NO_DEVICE", "NO_PIN"]):
      if key not in ports:
        ports[key] = [ port_num, 0 ]
        port_num += 1
      ports[key][1] |= pin[2] # build port mask
  # p ports
  # example: ports = {("MCU_GPIO", "F0"): [0, 240], ("MCU_GPIO", "B0"): [1, 14]}
  for v in ports.values():
    v[1] = '0x%02xU' % v[1]
  # p ports
  # example: ports = {("MCU_GPIO", "F0"): [0, "0xf0U"], ("MCU_GPIO", "B0"): [1, "0x0eU"]}
  #### build pins list ####
  pins = []
  for pin in raw_list:
    key = tuple(pin[0:2])
    if key in ports.keys():
      port_index = ports[key][0]
    else:
      port_index = "NO_PIN"
    pins.append([ port_index, '0x%02xU' % pin[2], '0x%02xU' % pin[3] ])
  # p pins
  # example: pins = [[0, "0x10U", "0x1U"], [0, "0x20U", "0x2U"], [0, "0x40U", "0x4U"], [0, "0x80U", "0x8U"], [1, "0x2U", "0x10U"], [1, "0x8U", "0x20U"], [1, "0x4U", "0x40U"]]
  return [ [ [ port[0][1], port[1][1], port[0][0] ] for port in ports.items() ], pins ]

def print_port(ports):
  print("    /* ( ( <port>, <mask>, <dev> ), ... ) */ \\")
  print("    ( ", end='')
  print(", \\\n      ".join([f"({port[0]}, {port[1]}, {port[2]})" for port in ports]), end='')
  print(" ),\\")

def print_pin(pins, is_input = False):
  if is_input:
    pins = [pin for pin in pins if pin[0] != "NO_PIN"]
  else:
    pins = [[0 if pin[0] == "NO_PIN" else pin[0], *pin[1:]] for pin in pins]
  print("    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \\")
  print("    ( ", end='')
  print(", \\\n      ".join([f"({pin[0]}, {pin[1]}, {pin[2]})" for pin in pins]), end='')
  print(" )")

if __name__ == '__main__':
  main()
