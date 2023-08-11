# Jocker 1800

![jocker1800]( https://i.imgur.com/aQEiE4Hh.jpg )

PCB Replacement for Austin 1800

* Keyboard Maintainer: [Maze Studio](https://github.com/mazestd)
* Hardware Supported: Jocker PCB, Atmega32u4
* Hardware Availability: Local Group Buy

Make example for this keyboard (after setting up your build environment):

    make mazestd/jocker:default

Flashing example for this keyboard:

    make mazestd/jocker:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (1,0) in the matrix or Escape Key and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
