# 3x3macropad

![3x3macropad](https://i.imgur.com/LMkcKOw.jpg)

The 3x3macropad is a small macropad with a cool OLED screen and rotary encoder.
It was inspired by stacked FR4 keyboards like the Discipline65.

* Keyboard Maintainer: [RarePotato8DE](https://github.com/rarepotato8de)
* Hardware Supported: 3x3macropad
* Hardware Availability: [Open source!](https://github.com/rarepotato8de/3x3macropad)

Make example for this keyboard (after setting up your build environment):

    make rarepotato8de/3x3macropad:default

Flashing example for this keyboard:

    make rarepotato8de/3x3macropad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,1) in the matrix (the top left one below the OLED) and plug in the keyboard
* **Physical reset button**: Short the two through hole pins on the back of the PCB (positioned at the rotary encoder)
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available