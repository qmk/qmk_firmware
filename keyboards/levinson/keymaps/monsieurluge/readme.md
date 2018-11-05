# monsieurluge's Levinson layout

## Design goals

- qwerty, and custom layouts
- increase the accessibility to the main coding symbols
- use a function key to access the multimedia functions
- do not use any of the 4 main fingers to WRITE IN UPPERCASE (use the thumb instead): one tap on the spacebar for a space character, hold for the SHIFT modifier

## Layouts

### qwerty

_todo description_

_todo layout picture_

### custom

_todo description_

_todo layout picture_

## Build

Make

`make levinson:monsieurluge`

Flash

```
sudo avrdude -p atmega32u4 -P /dev/ttyACM0 -c avr109 -U flash:w:levinson_rev2_monsieurluge.hex
```
