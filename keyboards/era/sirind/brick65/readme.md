# Brick65

![Brick65](https://i.imgur.com/qyQYWfjh.jpg)

Brick65 is a 65% ANSI layout Custom Keyboard

* Keyboard Maintainer: Pyupyu
* Hardware Supported: Brick65
* Hardware Availability: Syryan

## How to enter Bootloader Mode

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead

Make example for this keyboard (after setting up your build environment):

    make era/sirind/brick65:default

Flashing example for this keyboard:

    make era/sirind/brick65:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
