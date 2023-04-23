Find build documentation at the Hackaday.io site for [Yet another Modular split ergonomic Keyboard](https://hackaday.io/project/21164-yamsek)

a split keyboard, following the dactyl style of slightly curved keybard halves; and only one MCU running the whole show alongside an I2C portexpander in 'the other half'

YaMseK keyboard firmware
======================

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme](/).

## Building

for the default keymap:
```
$> make handwired/yamsek/atmega32u4:default:avrdude
```
