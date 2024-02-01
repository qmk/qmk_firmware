# Churrosoft Deck-8 (No LEDs version)

![ChurroDeck-8](https://i.imgur.com/NNmq8hzh.png)

A small 8-key macropad

* Keyboard Maintainer: [Polsaker](https://github.com/Polsaker)
* Hardware Supported: ChurroDeck PCV rev. 1b, 1c and 1d
* Hardware Availability: [churrosoft.ar](https://churrosoft.ar/deck)

Make example for this keyboard (after setting up your build environment):

    make churrosoft/deck8/noleds:default

Flashing example for this keyboard:

    make churrosoft/deck8/noleds:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Short the `JP1` jumper in the back side of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available