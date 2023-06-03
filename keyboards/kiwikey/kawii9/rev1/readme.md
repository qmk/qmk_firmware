# Kawii9 Rev1

![Kawii9 Rev1](http://kiwikey.vn/media/kawii9/kawii9_rev1.jpg)

A 3x3 keypad, comes with 2 options: solderable and hotswap.

* Keyboard Maintainer: [KiwiKey](https://github.com/kiwikey)
* Hardware Supported: Kawii9 rev1 PCB
* Hardware Availability: from Group-buy, or via KiwiKey Website (https://kiwikey.vn/mechkey/kawii9/)

Make example for this keyboard (after setting up your build environment):

    make kiwikey/kawii9/rev1:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
