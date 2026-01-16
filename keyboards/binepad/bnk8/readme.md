# BINEPAD BNK8

![BINEPAD BNK8](https://i.imgur.com/HFIZg48h.jpeg)

A compact 8-key 3x3 macropad with a rotary encoder at the top right.

* Keyboard Maintainer: [binepad](https://github.com/binepad)
* Hardware Supported: BINPAD BNK8
* Hardware Availability: [binepad.com](https://binepad.com/products/bnk8)

Make example for this keyboard (after setting up your build environment):

    make binepad/bnk8:default

Flashing example for this keyboard:

    make binepad/bnk8:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key) and plug in the keyboard
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
