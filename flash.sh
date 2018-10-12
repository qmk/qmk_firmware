echo "Sleeping for 5 seconds for keyboard to enter bootloader..."
sleep 5
dfu-programmer atmega32u4 erase
dfu-programmer atmega32u4 flash dz60_marianas.hex
dfu-programmer atmega32u4 reset
