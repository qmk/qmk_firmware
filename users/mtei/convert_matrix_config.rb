#!/usr/bin/ruby

# Copyright 2022 Takeshi Ishii (@mtei)
# SPDX-License-Identifier: GPL-2.0-or-later

require "yaml"

if ARGV.size != 1
   puts "usage: ruby #$0 <config_file or info.json>"
   exit 1;
end

$col_pins = nil
$col_pins_right = nil
$col_pins_ext = nil
$col_pins_ext_right = nil
$row_pins = nil
$row_pins_right = nil
$row_pins_ext = nil
$row_pins_ext_right = nil

$input_port_pin = nil
$output_port_pin = nil
$input_port_pin_right = nil
$output_port_pin_right = nil

def main
  read_configuration(ARGV[0])
  build_all_port_pin_lists()
  print_all_port_pin_lists()
end

def read_configuration(file)
  if file =~ /^.*info.json/
    read_configuration_from_info_json(file)
  else
    read_configuration_from_config_h(file)
  end
end

def build_all_port_pin_lists()
  $input_port_pin = build_port_pin_list($col_pins) if $col_pins
  # p $input_port_pin
  $input_port_pin = build_port_pin_list_ext($col_pins_ext) if $col_pins_ext
  # p $input_port_pin

  $output_port_pin = build_port_pin_list($row_pins) if $row_pins
  # p $output_port_pin
  $output_port_pin = build_port_pin_list_ext($row_pins_ext) if $row_pins_ext
  # p $output_port_pin

  $input_port_pin_right = build_port_pin_list($col_pins_right) if $col_pins_right
  # p $input_port_pin_right
  $input_port_pin_right = build_port_pin_list_ext($col_pins_ext_right) if $col_pins_ext_right
  # p $input_port_pin_right

  $output_port_pin_right = build_port_pin_list($row_pins_right) if $row_pins_right
  # p $output_port_pin_right
  $output_port_pin_right = build_port_pin_list_ext($row_pins_ext_right) if $row_pins_ext_right
  # p $output_port_pin_right
end

def print_all_port_pin_lists()
  puts("#pragma once")

  if $input_port_pin
    if $col_pins_ext
      puts(" /* #define EXTENDED_MATRIX_COL_PINS #{$col_pins_ext} */")
    else
      puts(" /* #define MATRIX_COL_PINS {#{$col_pins}} */")
      puts("#undef MATRIX_COL_PINS")
    end
    puts("#define SWITCH_MATRIX_INPUT_0 \\")
    print_port($input_port_pin[0])
    print_pin($input_port_pin[1], true)
    puts("")
  end

  if $output_port_pin
    if $row_pins_ext
      puts(" /* #define EXTENDED_MATRIX_ROW_PINS #{$row_pins_ext} */")
    else
      puts(" /* #define MATRIX_ROW_PINS {#{$row_pins}} */")
      puts("#undef MATRIX_ROW_PINS")
    end
    puts("#define SWITCH_MATRIX_OUTPUT_0 \\")
    print_port($output_port_pin[0])
    print_pin($output_port_pin[1])
    puts("")
  end

  if $input_port_pin_right
    if $col_pins_ext_right
      puts(" /* #define EXTENDED_MATRIX_COL_PINS_RIGHT {#{$col_pins_ext_right}} */")
    else
      puts(" /* #define MATRIX_COL_PINS_RIGHT {#{$col_pins_right}} */")
      puts("#undef MATRIX_COL_PINS_RIGHT")
    end
    puts("#define SWITCH_MATRIX_INPUT_1 \\")
    print_port($input_port_pin_right[0])
    print_pin($input_port_pin_right[1], true)
    puts("")
  end

  if $output_port_pin_right
    if $row_pins_ext_right
      puts(" /* #define EXTENDED_MATRIX_ROW_PINS_RIGHT #{$row_pins_ext_right} */")
    else
      puts(" /* #define MATRIX_ROW_PINS_RIGHT {#{$row_pins_right}} */")
      puts("#undef MATRIX_ROW_PINS_RIGHT")
    end
    puts("#define SWITCH_MATRIX_OUTPUT_1 \\")
    print_port($output_port_pin_right[0])
    print_pin($output_port_pin_right[1])
    puts("")
  end
end

def read_configuration_from_config_h(file)
  conf = `gcc -dM -E #{file} 2> /tmp/err | grep \"define MATRIX_\" `.split("\n")
  conf += `gcc -dM -E #{file} 2> /tmp/err | grep \"define EXTENDED_MATRIX_\" `.split("\n")
  conf.each {|c|
    if /[ \t]*#[ \t]*define[ \t]* MATRIX_COL_PINS[ \t]+{(.*)}/ =~ c
      $col_pins = $1
    end
    if /[ \t]*#[ \t]*define[ \t]* MATRIX_COL_PINS_RIGHT[ \t]+{(.*)}/ =~ c
      $col_pins_right = $1
    end
    if /[ \t]*#[ \t]*define[ \t]* EXTENDED_MATRIX_COL_PINS[ \t]+(.*)/ =~ c
      $col_pins_ext = $1
    end
    if /[ \t]*#[ \t]*define[ \t]* EXTENDED_MATRIX_COL_PINS_RIGHT[ \t]+(.*)/ =~ c
      $col_pins_ext_right = $1
    end
    if /[ \t]*#[ \t]*define[ \t]* MATRIX_ROW_PINS[ \t]+{(.*)}/ =~ c
      $row_pins = $1
    end
    if /[ \t]*#[ \t]*define[ \t]* MATRIX_ROW_PINS_RIGHT[ \t]+{(.*)}/ =~ c
      $row_pins_right = $1
    end
    if /[ \t]*#[ \t]*define[ \t]* EXTENDED_MATRIX_ROW_PINS[ \t]+(.*)/ =~ c
      $row_pins_ext = $1
    end
    if /[ \t]*#[ \t]*define[ \t]* EXTENDED_MATRIX_ROW_PINS_RIGHT[ \t]+(.*)/ =~ c
      $row_pins_ext_right = $1
    end
  }
end

def read_configuration_from_info_json(file)
  info = open(file, 'r') { |f| YAML.load(f) }
  if info["matrix_pins"]
      $col_pins = info["matrix_pins"]["cols"].join(",")
      $row_pins = info["matrix_pins"]["rows"].join(",")
  else
    puts("ERROR: #{file} does not contain matrix_pins information.")
    exit(1)
  end
end

def build_port_pin_list(pins)
  # p pins
  #    if source data is '#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 }'
  # example: pins = " F4, F5, F6, F7, B1, B3, B2 "
  pin_number = 0
  raw_list = pins.split(",").map{|pin| pin.strip}.map{|pin|
    pin_number += 1
    if pin == "NO_PIN"
      port = "NO_PIN"
      mask = 0
      ["NO_DEVICE", port, mask, 0]
    else
      /([A-Z]+)([0-9]*)/ =~ pin.strip;
      port = $1+"0"
      mask = (1<<$2.to_i)
      ["MCU_GPIO", port, mask, (1<<(pin_number - 1))]
    end
  }
  # p raw_list
  # example: raw_list = [["MCU_GPIO", "F0", 16, 1], ["MCU_GPIO", "F0", 32, 2], ["MCU_GPIO", "F0", 64, 4], ["MCU_GPIO", "F0", 128, 8], ["MCU_GPIO", "B0", 2, 16], ["MCU_GPIO", "B0", 8, 32], ["MCU_GPIO", "B0", 4, 64]]
   build_port_pin_list_sub(raw_list)
end

def build_port_pin_list_ext(pins)
  # p pins
  #   if source data is
  #      '#define EXTENDED_MATRIX_COL_PINS \
  #          (MCU_GPIO, F0, 4), (MCU_GPIO, F0,5 ), (MCU_GPIO, F0,6 ), \
  #          (MCU_GPIO, F0, 7), (MCU_GPIO, B0, 1), (MCU_GPIO, B0, 3), (MCU_GPIO, B0, 2)'
  # example: pins = "(MCU_GPIO, F0, 4), (MCU_GPIO, F0,5 ), (MCU_GPIO, F0,6 ), (MCU_GPIO, F0, 7), (MCU_GPIO, B0, 1), (MCU_GPIO, B0, 3), (MCU_GPIO, B0, 2)"
  pin_number = 0
  sepalate_pins = pins.strip.gsub(/^\(/,"").gsub(/\)$/,"").split(/\)[ ]*,[ ]*\(/)
  raw_list = sepalate_pins.map{|pin|
    pin = pin.split(",")
    dev = pin[0].strip
    port = pin[1].strip
    pin_number += 1
    if dev == "NO_DEVICE" || port == "NO_PIN"
      ["NO_DEVICE", "NO_PIN", 0, 0]
    else
      mask = (1<<pin[2].to_i)
      [dev, port, mask, (1<<(pin_number - 1))]
    end
  }
  # p raw_list
  # example: raw_list = [["MCU_GPIO", "F0", 16, 1], ["MCU_GPIO", "F0", 32, 2], ["MCU_GPIO", "F0", 64, 4], ["MCU_GPIO", "F0", 128, 8], ["MCU_GPIO", "B0", 2, 16], ["MCU_GPIO", "B0", 8, 32], ["MCU_GPIO", "B0", 4, 64]]
   build_port_pin_list_sub(raw_list)
end

def build_port_pin_list_sub(raw_list)
  #### build ports list ####
  port_num = 0;
  ports = {}
  raw_list.each {|pin|
    if pin[0..1] != ["NO_DEVICE", "NO_PIN"]
      if ports[pin[0..1]] == nil
        ports[pin[0..1]] = [ port_num, 0 ]
        port_num += 1
      end
      ports[pin[0..1]][1] |= pin[2] # build port mask
    end
  }
  # p ports
  # example: ports = {["MCU_GPIO", "F0"]=>[0, 240], ["MCU_GPIO", "B0"]=>[1, 14]}
  ports.each {|port|
     port[1][1] = sprintf("0x%02xU", port[1][1])
  }
  # p ports
  # example: port_list = {["MCU_GPIO", "F0"]=>[0, "0xf0U"], ["MCU_GPIO", "B0"]=>[1, "0x0eU"]}
  #### build pins list ####
  pins = raw_list.map {|pin|
    if ports[pin[0..1]]
      port_index = ports[pin[0..1]][0]
    else
      port_index = "NO_PIN"
    end
    [ port_index, sprintf("0x%02xU",pin[2]), sprintf("0x%02xU",pin[3]) ]
  }
  # p pins
  # example: pins = [[0, "0x10U", "0x1U"], [0, "0x20U", "0x2U"], [0, "0x40U", "0x4U"], [0, "0x80U", "0x8U"], [1, "0x2U", "0x10U"], [1, "0x8U", "0x20U"], [1, "0x4U", "0x40U"]]
  return [ ports.map{ |port| [port[0][1], port[1][1], port[0][0] ] }, pins ]
end

def print_port(ports)
  puts("    /* ( ( <port>, <mask>, <dev> ), ... ) */ \\")
  print("    ( ")
  print ports.map {|port| "(#{port[0]}, #{port[1]}, #{port[2]})" }.join(", \\\n      ")
  puts(" ),\\")
end

def print_pin(pins, is_input = false)
  if is_input
    pins = pins.delete_if{ |pin| pin[0] == "NO_PIN" }
  else
    pins = pins.map { |pin|
      pin[0] = 0 if pin[0] == "NO_PIN"
      pin
    }
  end
  puts("    /* ( ( <port_index>, <port_mask>, <matrix_row_mask> ), ... ) */ \\")
  print("    ( ")
  print pins.map {|pin| "(#{pin[0]}, #{pin[1]}, #{pin[2]})" }.join(", \\\n      ")
  puts(" )")
end

main
