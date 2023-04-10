# Dactyl Manuform 4x6_56

This variant of a Dactyl Manuform 4x6 has a 4 key bottom row, like the 5x7 variant, instead of the default 2. Totalling the amount of keys for this variant to 56.

`4x6`*(Base variant)*`_56`*(Total key count)*

* Keyboard Maintainer: [Tom Short](https://github.com/tshort)
* Hardware Supported: 2x [Arduino Pro Micro](https://www.sparkfun.com/products/12640) controller
* Hardware Availability: [Dactyl Manuform](https://github.com/tshort/dactyl-keyboard#wiring) github for Bill of Materials and build guide

Make example for this keyboard (after setting up your build environment):
```
    make handwired/dactyl_manuform/4x6_56:default
```
Flashing example for this keyboard:
```
    make handwired/dactyl_manuform/4x6_56:default:flash
```
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available