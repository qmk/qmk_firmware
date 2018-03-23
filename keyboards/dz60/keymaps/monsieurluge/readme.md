# monsieurluge's DZ60 layout

## Design goals

- increase the accessibility to the main coding symbols
- use a function key to access the multimedia functions
- do not use any of the 4 main fingers to WRITE IN UPPERCASE (use the thumb instead): one tap on the spacebar for a space character, hold for the SHIFT modifier

## Build

Make

`make dz60:monsieurluge`

Flash

```
sudo dfu-programmer atmega32u4 erase
sudo dfu-programmer atmega32u4 flash dz60_monsieurluge.hex
sudo dfu-programmer atmega32u4 reset
```
