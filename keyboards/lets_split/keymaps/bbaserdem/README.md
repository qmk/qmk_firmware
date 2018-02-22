# Lets Split Layout

Built this planck layout to use DVORAK with an unorthodox Turkish layout.
Adapted to Let's Split. Check my users file for more info.

# Usage

If haven't done so, flash halves with their respective EEPROM,
and flash the hex file without deleting EEPROM.
For the left half;

```
make lets_split/rev2:bbaserdem
COM_PORT="$(ls /dev/ttyACM*)"
sudo avrdude -p atmega32u4 -P $COM_PORT -c avr109 -D -U flash:w:.build/lets_split_rev2_bbaserdem.hex
sudo avrdude -p atmega32u4 -P $COM_PORT -c avr109 -U eeprom:w:keyboards/lets_split/eeprom-lefthand.eep
```

For the right half;
``````
make lets_split/rev2:bbaserdem_right
COM_PORT="$(ls /dev/ttyACM*)"
sudo avrdude -p atmgea34u4 -P $COM_PORT -c avr109 -U flash:w:.build/lets_split_rev2_bbaserdem_right.hex
sudo avrdude -p atmega32u4 -P $COM_PORT -c avr109 -U eeprom:w:keyboards/lets_split/eeprom-righhand.eep
```
