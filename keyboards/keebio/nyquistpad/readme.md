# Nyquistpad

A 5x6 macropad keyboard based off of a prototype Nyquist PCB.

* Keyboard Maintainer: Keebio
* Hardware Supported: Nyquistpad PCB
* Hardware Availability: [Keebio](https://keeb.io/)

Make example for this keyboard (after setting up your build environment):

    make keebio/nyquistpad:default

Flashing example for this keyboard:

    make keebio/nyquistpad:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Press and hold the button on the back of the PCB for at least 2 seconds and let go, or double-press the button
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
