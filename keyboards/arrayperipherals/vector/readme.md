# The Vector Macropad

![The Vector](https://i.imgur.com/rmy76bp.png)

A small (1x4) macropad with a rotary. [More info at arrayperipherals.com](https://www.arrayperipherals.com/)

* Keyboard Maintainer: [David Doan](https://github.com/daviddoan)
* Hardware Supported: Custom PCB with Atmega32u4 processor
* Hardware Availability: [arrayperipherals.com](https://www.arrayperipherals.com/)

Make example for this keyboard (after setting up your build environment):

    make arrayperipherals/vector:default

Flashing example for this keyboard:

    make arrayperipherals/vector:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (left most from the rotary)
* **Physical reset button**: Briefly double press the button on the back of the PCB 