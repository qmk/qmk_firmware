# Lets Split - Right Half

Keymap for my right half, to be used as a numpad.

# Usage

Make sure you have no other ProMicro devices connected.
Flash the eeprom with the right hand. From base directory;

```
COM_PORT="$(ls /dev/ttyACM*)"
sudo avrdude -p atmega32u4 -P $(COM_PORT) -c avr109 -U eeprom:w:keyboards/lets_split/eeprom-righhand.eep
```

Build the hex file, and flash it
```
make lets_split/rev2:bbaserdem_right:w
sudo avrdude -p atmgea34u4 -P `ls /dev/ttyACM*` -c avr109 -D -U flash:.build/lets_split_rev2_bbaserdem_right.hex
```

I find it easier to use sudo rather than go through udev rules.
