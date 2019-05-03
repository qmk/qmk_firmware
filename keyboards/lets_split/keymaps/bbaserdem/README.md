# Lets Split Layout

Check out [user readme](../../../../users/bbaserdem/README.md) for more info.

# Usage

**These commands depend on there being no other arduino connected!**
Also udev rules can be set instead of using sudo.
Please unplug all other usb devices.

To make the hex files;
```
make lets_split/rev2:bbaserdem
make lets_split/rev2:bbaserdem_right
```

For the left half, after plugging in and resetting; (from repo main directory)
```
sudo avrdude -p atmega32u4 -P "$(ls /dev/ttyACM*)" -c avr109 -D -U flash:w:.build/lets_split_rev2_bbaserdem.hex
sudo avrdude -p atmega32u4 -P "$(ls /dev/ttyACM*)" -c avr109 -U eeprom:w:keyboards/lets_split/eeprom-lefthand.eep
```

For the right half;
```
sudo avrdude -p atmgea34u4 -P "$(ls /dev/ttyACM*)" -c avr109 -D -U flash:w:.build/lets_split_rev2_bbaserdem_right.hex
sudo avrdude -p atmega32u4 -P "$(ls /dev/ttyACM*)" -c avr109 -U eeprom:w:keyboards/lets_split/eeprom-righhand.eep
```
