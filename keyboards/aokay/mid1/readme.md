# MID.1

![MID.1 photo](https://i.imgur.com/aPsvygY.jpeg)

## Description

A 40% keyboard with a staggered 4x12 layout and hotswap PCB.

* Keyboard Maintainer: [Sean O'Neill](https://github.com/oneillseanm)
* Hardware Supported: MID.1
* Hardware Availability: [A.Okay! product page](https://www.aokay.cool)

## Setup

Make example for this keyboard (after setting up your build environment):

    make aokay/mid1:default

Flashing example for this keyboard:

    make aokay/mid1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in three ways:

* **Bootmagic reset**: Hold down `Esc` and plug in the keyboard. `Esc` is assigned to the top left key in the default keymap.
* **Keycode in layout**: Press `Fn+ESC` for `QK_BOOT`. `Fn` is assigned to the key to the right of the spacebar/split spacebar in the default keymap.
* **Physical reset button**: Briefly press the button on the back of the PCB, accessible through the bottom case.