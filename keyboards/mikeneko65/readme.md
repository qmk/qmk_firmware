# Mikeneko 65

A simple 65% keyboard

* Keyboard Maintainer: [takishim](https://github.com/takishim)
* Hardware Supported: Mikeneko 65
* Hardware Availability: [Open source on GitHub](https://github.com/takishim/mikeneko65/)

Make example for this keyboard (after setting up your build environment):

    make mikeneko65:default

Flashing example for this keyboard:

    make mikeneko65:default:flash

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

ぶSee the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
