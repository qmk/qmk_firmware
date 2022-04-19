# 5x5_macropad

![m40](https://i.imgur.com/bWXH3FVl.jpeg)

This is very simple 5x5 macropad for general use. It does not come with any particular layout, it is assumed that layouts will be built on the qmk configurator site. Row and column pins start on the edge of Arduino, if smaller board is required, you can simply connect only first x row/column pairs to the board and get the size of the board you need.

* Keyboard Maintainer: [Tomek](https://github.com/m40-dev) (discord: m40#4792)
* Hardware Supported: 3D Printed, handwired, using Arduino Pro-Micro (Atmega32U4) for controller
* Hardware Availability: https://www.thingiverse.com/thing:5239739

Make example for this keyboard (after setting up your build environment):

    make handwired/m40/5x5_macropad:default

Flashing example for this keyboard:

    make handwired/m40/5x5_macropad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `RESET` if it is available. In default layout (if you flashed it already once) it is the top-right button.
