# Dactyl Manuform (5x6) with 6 thumb cluster

The [Dactyl-Manuform](https://github.com/tshort/dactyl-keyboard) is a split curved keyboard based on the design of [adereth dactyl](https://github.com/adereth/dactyl-keyboard) and thumb cluster design of the [manuform](https://geekhack.org/index.php?topic=46015.0) keyboard, the hardware is similar to the let's split keyboard. All information needed for making one is in the first link.

![Imgur](https://i.imgur.com/MvtMG1vh.png)

* Keyboard Maintainer: fgoodwin
* Hardware Supported: Pro Micro Micro Micro USB or USB C

Make example for this keyboard (after setting up your build environment):

    make handwired/dactyl_manuform/5x6_6:default

Flashing example for this keyboard:

    make handwired/dactyl_manuform/5x6_6:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Enter the bootloader in 2 ways:
**Physical reset button**: Briefly press the reset button on the bottom of the case, or bridge the reset and ground pins momentarily on the pro micro
**Keycode in layout**: Press the key mapped to `QK_BOOT` (by default hold down `MO(1)` and press the left most key in row 5 on the left hand half of the keyboard)