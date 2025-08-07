# BINEPAD BNK9

![BINEPAD BNK9](https://i.imgur.com/FrkVRhhh.jpg)

A 3x3 macropad with a large rotary encoder.

* Keyboard Maintainer: [binepad](https://github.com/binepad)
* Hardware Supported: BINPAD BNK9
* Hardware Availability: [binepad.com](https://www.binepad.com/product-page/bnk9)

Make example for this keyboard (after setting up your build environment):

    make binepad/bnk9:default

Flashing example for this keyboard:

    make binepad/bnk9:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0x0) in the matrix (the 'knob' / rotary encoder) and plug in the keyboard.
* **Physical reset button**: Briefly press the PCB button located on the back of the PCB.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` *(or* `RESET` *in VIA)* if it is available.
