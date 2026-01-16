# Cornia Keyboard

![Cornia v1](https://i.imgur.com/3vRlvi3.jpeg)

A split keyboard with 3x6 column strongly staggered keys and 3 thumb keys

* Keyboard Maintainer: [Vaarai](https://github.com/Vaarai) 
* Hardware Supported: Cornia PCB, RP2040 / 0xCB-Helios
* Hardware Availability: [PCB Data](https://github.com/Vaarai/Cornia)

Make example for this keyboard (after setting up your build environment):

    make cornia/v1:default

Flashing example for this keyboard:

    make cornia/v1:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK ? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

The Cornia PCBs have a reset button on the bottom side near to the TRRS jack.

To enter in to the bootloader you can either:
- Hold reset when plugging in that half of the keyboard.
- Double press reset if firmware was already flashed and if RP2040 is used
- Press NAV+NUM+ESC if firmware was already flashed no matter what controller is used

## Keymaps

Two keymaps are available for now, below are their [KLE](https://www.keyboard-layout-editor.com/) views:
- [Default QWERTY layout for Cornia keyboard](https://www.keyboard-layout-editor.com/#/gists/5af136790cefe4b35cdf02ca52c1fccc)
- [Fire layout for Cornia keyboard](https://www.keyboard-layout-editor.com/#/gists/a40345c92e1f3f326426ef890ebf4d1c) (Based on [Fire (Oxey)](https://docs.google.com/document/d/1Ic-h8UxGe5-Q0bPuYNgE3NoWiI8ekeadvSQ5YysrwII) layout)

## OLED Display & Cirque Trackpad

The Cornia Keyboard also support OLED Display and Cirque Trackpad through I²C, an implementation is available in `fire` keymap.

To use it please make with the following command:

    make cornia/v1:fire

And flash with:

    make cornia/v1:fire:flash