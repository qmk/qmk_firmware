#!/bin/bash
sudo dfu-programmer atmega32u4 erase --force
sudo dfu-programmer atmega32u4 flash clear_flash.hex
sudo dfu-programmer atmega32u4 reset
