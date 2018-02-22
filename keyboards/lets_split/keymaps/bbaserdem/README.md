# Lets Split Layout

Built this planck layout to use DVORAK with an unorthodox Turkish layout.
Adapted to Let's Split. Check my users file for more info.

# Usage

If haven't done so, flash halves with their respective EEPROM,
and flash the hex file without deleting EEPROM.
For the left half;

```
COM_PORT="$(ls /dev/ttyACM*)"
sudo avrdude -p atmega32u4 -P $(COM_PORT) -c avr109 -U eeprom:w:keyboards/lets_split/eeprom-righthand.eep
make lets_split/rev2:bbaserdem
sudo avrdude -p atmgea34u4 -P `ls /dev/ttyACM*` -c avr109 -D -U flash:.build/lets_split_rev2_bbaserdem.hex
```

For the right half;
``````
COM_PORT="$(ls /dev/ttyACM*)"
sudo avrdude -p atmega32u4 -P $(COM_PORT) -c avr109 -U eeprom:w:keyboards/lets_split/eeprom-righhand.eep
make lets_split/rev2:bbaserdem_right
sudo avrdude -p atmgea34u4 -P `ls /dev/ttyACM*` -c avr109 -D -U flash:.build/lets_split_rev2_bbaserdem_right.hex
```
