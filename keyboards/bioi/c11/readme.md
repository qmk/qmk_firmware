# Cary Works x Basic I/O Instruments C11

Compact keypad with 11 keys.

![C11](https://i.imgur.com/muzhDG0h.jpg)

* Keyboard Maintainer: [Basic I/O Instruments (Scott Wei)](https://github.com/scottywei)
* Hardware Supported: [Basic I/O Instruments (Scott Wei)](https://github.com/scottywei)
* Hardware Availability: (https://www.zfrontier.com/app/flow/e3pxpPvJpnnL)

Make example for this keyboard (after setting up your build environment):

    make bioi/c11:default

Flashing example for this keyboard:

    make bioi/c11:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
