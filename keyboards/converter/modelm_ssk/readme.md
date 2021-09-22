# modelm_ssk

![IBM Model M Space-Saving Keyboard](https://i.imgur.com/CSXrQI5.jpg)

This is a QMK firmware configuration for the IBM Model M Space-Saving Keyboard (SSK). Based on [this project](https://github.com/qmk/qmk_firmware/tree/master/keyboards/converter/modelm101), it features a few slight improvements and, most importantly, a full remapping to match the SSK's matrix, which differs from its full-sized cousins. The modification is easily reversible, as no part of the keyboard is permanently changed. Just take out the replacement controller and reinstall the original, should you desire.

The numpad layer (accessed with Shift + Scroll Lock as with the original controller) is mapped to layer 7 by default. All non-numpad keys are transparent.

**Note:** As of this writing, this configuration has only been tested on the 1392464 SSK. It's possible other models differ in their internal matrices. Should the provided matrix not work for you (and you are certain of your connections), you can enable debugging with `CONSOLE_ENABLE = yes` in `rules.mk` and by following the directions in `default/keymap.c`. Once done, [QMK Toolbox](https://github.com/qmk/qmk_toolbox) will display row/col information to help you remap `modelm_ssk.h`.

## Requirements

* [Teensy++ 2.0](https://www.pjrc.com/store/teensypp.html) - I recommend buying one with pins already attached
* A Trio-Mate 16-pin ribbon connector (6-520315-6 or 6-520415-6)
* A Trio-Mate 8-pin ribbon connector (5-120628-8 or 5-520314-8). Alternatively, two 16-pin connectors can be used if the 8-pin is out of stock. Just be sure to line up your pins correctly
* Breadboard or perfboard. A perfboard is recommended due to its reduced height and low clearance inside the chassis
* Mini-B to USB-A cable
* Jumper wires and wire strippers/cutters
* Soldering iron if not using a breadboard

## Setup

![Finished controller](https://i.imgur.com/m1yuo4F.jpg)

The controller uses the following mapping (in zero-indexed hex):

```
Column: 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F
Pin:   C7 C6 C5 C4 C3 C2 C1 C0 E1 E0 D7 D5 D4 D3 D2 D1
--------------------------------------------------------
Row:  0  1  2  3  4  5  6  7
Pin: F0 F1 F2 F3 F4 F5 F6 F7
```

**IMPORTANT:** It is necessary to skip pin D6 on the Teensy. There is an LED attached to this pin, which can cause interference with registering keys. Alternatively, you can remove the LED from the board, which is likely to be a permanent modification of the Teensy. The choice is yours. I am not responsible for any damage to your Teensy or keyboard.

## A note on the Unicomp Mini M

This configuration will not work out of the box with the [Unicomp Mini M](https://www.pckeyboard.com/page/product/MINI_M). That keyboard uses a 16x12 matrix rather than the SSK's 16x8 in order to reduce occurrences of 2KRO lockup. It also features lock lights, which the SSK lacks. However, it should be possible to map out the Mini M's matrix to get it working.

## Maintainer

* Keyboard Maintainer: [tiltowait](https://github.com/tiltowait), original work by [iw0rm3r](https://github.com/iw0rm3r)
* Hardware Supported: Teensy 2.0++ board by PJRC
* Hardware Availability: https://www.pjrc.com/store/teensypp.html

## Building

Make example for this keyboard (after setting up your build environment):

    make converter/modelm_ssk:default

You must press the button on the Teensy to enter the bootloader the first time. Afterward, so long as you keep `COMMAND_ENABLE = yes` in `rules.mk` (enabled by default), you can use `Left Shift + Right Shift + B` to enter the bootloader. With this method, you can omit `:teensy` from the end of the `make` command.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
