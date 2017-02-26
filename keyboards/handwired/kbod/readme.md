KBOD keyboard firmware
======================

KBOD is a 60% Keyboard kit, hand-wired, with Arduino Micro as its controller. It's utilize 8x8 matrix and has layout similar to GH-60

## Quantum MK Firmware

For the full Quantum feature list, see [the parent readme](/).

## Building

Download or clone the whole firmware and use ```make handwired-kbod-default``` to generate the .hex file. You may flash it with avrdude

## Flashing
Something along this line:

```
avrdude -p m32u4 -c avr109 -P <COM PORT> -C <avrdude conf file> -e -u flash:w:handwired_kbod_default.hex
```

[More info](https://github.com/fudanchii/keyboard_of_disapproval)