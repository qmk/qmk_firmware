# Dactyl Manuform 6x6_5_2

![Dactyl Manufrom 6x6_5_2](https://i.imgur.com/j8dsBgs.jpeg)

## Description

This variant of a Dactyl Manuform 4x6 has a 4 key bottom row, like the 5x7 variant, instead of the default 2. Totalling the amount of keys for this variant to 76.

`4x6`*(Base variant)*`_76`*(Total key count)*

* Keyboard Maintainer: dmik
* Hardware Supported: 2x [Arduino Pro Micro](https://www.sparkfun.com/products/12640) controller
* Hardware Availability: [Dactyl Manuform](https://github.com/tshort/dactyl-keyboard#wiring) github for Bill of Materials and build guide

Make example for this keyboard (after setting up your build environment):
```
    make handwired/dactyl_manuform/6x6_5_2:default
```
Flashing example for this keyboard:
```
    make handwired/dactyl_manuform/6x6_5_2:default:flash
```
See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Build

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
After setting up your build environment you can try to build it with those commands.


## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at F1 for left side, and F7 for right side.
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
