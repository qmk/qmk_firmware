# Big Knob

![big_knob](https://i.imgur.com/KLS0O7Zh.png)

A 3D printed single encoder volume knob with a SPI Screen.

* Keyboard Maintainer: [jpe230](https://github.com/jpe230)
* Hardware Supported: Big Knob PCB, Sparkfun ProMicro RP2040 (*See notes*)
* Hardware Availability: <https://github.com/Jpe230/big_knob>
## Features

The Big Knob was designed to be easy to assemble:
* Designed to be used with a RP2040 board (*See notes*)
* ST7735 0.96 inch color display
* RGBLight
* Easy to 3D print

### Notes
You can use any compatible RP2040 board (I.E.: KB2040, Elite Pi, etc), but you will need to modify the pin definition to match you board

## Flashing

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb jpe230/big_knob -km default

Flashing example for this keyboard:

    qmk flash -kb jpe230/big_knob -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Building Instructions

You can find the required materials and the instructions to build your own Big Knob in the [project repo](https://github.com/Jpe230/big_knob)

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the encoder buitton and plug in the keyboard
* **Physical reset button**: Briefly press the reset button on the front of the RP2040 board
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
