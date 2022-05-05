#!/usr/bin/ruby

# Copyright 2022 Takeshi Ishii (@mtei)
# SPDX-License-Identifier: GPL-2.0-or-later

if ARGV.size != 1
   puts "usage: ruby #$0 <config_file>"
   exit 1;
end

#------ read config
conf = `gcc -dM -E #{ARGV[0]} 2> /tmp/err | grep \"define MATRIX_\" `.split("\n")
col_pins = nil
col_pins_right = nil
row_pins = nil
row_pins_right = nil
conf.each {|c|
  if /[ \t]*#[ \t]*define[ \t]* MATRIX_COL_PINS[ \t]*{(.*)}/ =~ c
    col_pins = $1
  end
  if /[ \t]*#[ \t]*define[ \t]* MATRIX_COL_PINS_RIGHT[ \t]*{(.*)}/ =~ c
    col_pins_right = $1
  end
  if /[ \t]*#[ \t]*define[ \t]* MATRIX_ROW_PINS[ \t]*{(.*)}/ =~ c
    row_pins = $1
  end
  if /[ \t]*#[ \t]*define[ \t]* MATRIX_ROW_PINS_RIGHT[ \t]*{(.*)}/ =~ c
    row_pins_right = $1
  end
}

#------ make port & pin list
def build_port_pin_list(pins)
  pin_number = 0
  raw_list = pins.split(",").map{|pin| pin.strip}.map{|pin|
    /([A-Z])([0-9]*)/ =~ pin.strip;
    port = $1+"0"
    mask = (1<<$2.to_i)
    pin_number += 1
    [port, mask, (1<<(pin_number - 1))]
  }
  # p raw_list
  # example: raw_list = [["F0", 16, 1], ["F0", 32, 2], ["F0", 64, 4], ["F0", 128, 8], ["B0", 2, 16], ["B0", 8, 32], ["B0", 4, 64]]
  port_num = 0;
  ports = {}
  raw_list.each {|pin|
    if ports[pin[0]] == nil
      ports[pin[0]] = [ port_num, 0 ]
      port_num += 1
    end
    ports[pin[0]][1] |= pin[1] # build port mask
  }
  # p ports
  # example: ports = {"F0"=>[0, 240], "B0"=>[1, 14]}
  ports.each {|port|
     port[1][1] = sprintf("0x%02x", port[1][1])
  }
  # p ports
  # example: port_list = {"F0"=>[0, "0xf0"], "B0"=>[1, "0xe"]}
  pins = raw_list.map {|pin| [ ports[pin[0]][0], sprintf("0x%02x",pin[1]), sprintf("0x%02x",pin[2]) ] }
  # p pins
  # example: pins = [[0, "0x10", "0x1"], [0, "0x20", "0x2"], [0, "0x40", "0x4"], [0, "0x80", "0x8"], [1, "0x2", "0x10"], [1, "0x8", "0x20"], [1, "0x4", "0x40"]]
  return [ ports.map{ |port| [port[0], port[1][1] ] }, pins ]
end

input_port_pin = build_port_pin_list(col_pins) if col_pins
  # p input_port_pin
output_port_pin = build_port_pin_list(row_pins) if row_pins
  # p output_port_pin

input_port_pin_right = build_port_pin_list(col_pins_right) if col_pins_right
  # p input_port_pin_right
output_port_pin_right = build_port_pin_list(row_pins_right) if row_pins_right
  # p output_port_pin_right

#------  print port & pin list
def print_port(ports)
  puts("    /* ( ( <port>, <mask> [, <dev>] ), ... ) */ \\")
  print("    ( ")
  print ports.map {|port| "(#{port[0]}, #{port[1]})" }.join(", \\\n      ")
  puts(" ),\\")
end

def print_pin(pins)
  puts("    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \\")
  print("    ( ")
  print pins.map {|pin| "(#{pin[0]}, #{pin[1]}, #{pin[2]})" }.join(", \\\n      ")
  puts(" )")
end

if input_port_pin
  puts(" /* #define MATRIX_COL_PINS {#{col_pins}} */")
  puts("#define SWITCH_MATRIX_INPUT_0 \\")
  print_port(input_port_pin[0])
  print_pin(input_port_pin[1])
  puts("")
end

if output_port_pin
  puts(" /* #define MATRIX_ROW_PINS {#{row_pins}} */")
  puts("#define SWITCH_MATRIX_OUTPUT_0 \\")
  print_port(output_port_pin[0])
  print_pin(output_port_pin[1])
  puts("")
end

if input_port_pin_right
  puts(" /* #define MATRIX_COL_PINS_RIGHT {#{col_pins_right}} */")
  puts("#define SWITCH_MATRIX_INPUT_1 \\")
  print_port(input_port_pin_right[0])
  print_pin(input_port_pin_right[1])
  puts("")
end

if output_port_pin_right
  puts(" /* #define MATRIX_ROW_PINS_RIGHT {#{row_pins_right}} */")
  puts("#define SWITCH_MATRIX_OUTPUT_1 \\")
  print_port(output_port_pin_right[0])
  print_pin(output_port_pin_right[1])
  puts("")
end

