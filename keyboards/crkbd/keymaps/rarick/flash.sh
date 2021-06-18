#!/usr/bin/env bash

if [ $# -ne 3 ]; then
  echo "Usage: source flash.sh BUS DEVICE HEX_FILE"
fi

sudo dfu-programmer "atmega32u4:$1,$2" erase --force
sudo dfu-programmer "atmega32u4:$1,$2" flash --debug 3 --eeprom "$3"
sudo dfu-programmer "atmega32u4:$1,$2" flash --debug 3 "$3"
