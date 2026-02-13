# 3x3x2 Direct In

Custom 3x3x2 (18-key) macropad using Pro Micro ATmega32u4 with direct pin wiring (no diodes).

## Features
- 18 direct pins
- USB HID keyboard

([3x3x2_direct_in](https://imgur.com/a/ZZ30VC0))

* Keyboard Maintainer: [LouisB](https://github.com/LouisB)
* Hardware Supported: Arduino Pro Micro Mini Clone
* Hardware Availability: https://golem.hu/article/pro-micro-pinout/#:~:text=If%20you%20use%20the%20Pro%20Micro%20outside,on%20its%20PCB%20to%20the%20AVR%20ones.

Make example for this keyboard (after setting up your build environment):

    make 3x3x2_direct_in:default

Flashing example for this keyboard:

    make 3x3x2_direct_in:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead

