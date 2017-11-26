`eeprom_reset.hex` is to reset the eeprom on the Atmega32u4, like this:

    dfu-programmer atmega32u4 erase
    dfu-programmer atmega32u4 flash --eeprom eeprom_reset.hex

 You'll need to reflash afterwards, because DFU requires the flash to be erased before messing with the eeprom.
