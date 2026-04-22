# Zer0Pad

![Zer0Pad](https://i.imgur.com/placeholder.jpg)

A compact 3x3 ortholinear macropad.

* Keyboard Maintainer: [Leon Sieber](https://github.com/lesieber)
* Hardware Supported: Pro Micro (ATmega32U4)
* Hardware Availability: Custom PCB

## Features

- 9-key 3x3 ortholinear layout
- Bootmagic Lite support

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top-left key while plugging in the keyboard
* **Physical reset button**: Short the RST and GND pins on the Pro Micro
* **Keycode in layout**: Press the key mapped to `QK_BOOT` (default: bottom-right key)

## Building

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb lesieber/zer0pad -km default

Flashing example for this keyboard:

    qmk flash -kb lesieber/zer0pad -km default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.
