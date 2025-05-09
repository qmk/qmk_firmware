# DMOTE

![DMOTE](https://i.imgur.com/JYkB6LBh.jpg)

The “**D**actyl-**M**anuForm: **O**pposable **T**humb **E**dition” is made from a Clojure
application maintained [here](https://github.com/veikman/dactyl-keyboard).
The application supports varied physical layouts and therefore matrices.
This physical variability is its main feature; its QMK firmware is ordinary.

* Keyboard Maintainer: [Viktor Eikman](https://github.com/veikman/)
* Hardware Supported: Pro Micro and clones

Make example for this keyboard (after setting up your build environment):

    make handwired/dmote:default

Flashing example for this keyboard:

    make handwired/dmote:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
