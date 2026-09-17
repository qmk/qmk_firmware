# zos65s

The ZOS65S is a sodlerable PCB for the ZOS 65 keyboard.

* Keyboard Maintainer: [Zenn](https://github.com/ZOSKB)
* Hardware Supported: Proprietary PCB using ATMEGA32U4 controller
* Hardware Availability: This will be made available at the ZOS Keyboards website when sales go live (https://www.zoskb.com)

Make example for this keyboard (after setting up your build environment):

    make zos/65s:default

Flashing example for this keyboard:

    make zos/65s:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
