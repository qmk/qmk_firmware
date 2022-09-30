# Split_5x7

![Split_5x7](https://i.imgur.com/fVw8al1h.jpg)

A handwired Split keyboard with the unusual layout of 5x7 on either side.

3d print files will be made available soon. 

* Keyboard Maintainer: [Stefan](https://github.com/stef9998)
* Hardware Supported: Pro Micro

Make example for this keyboard (after setting up your build environment):

    make handwired/stef9998/split_5x7/rev1:default

Flashing example for left side:

    make handwired/stef9998/split_5x7/rev1:default:avrdude-split-left

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

How to enter the bootloader:
* **Keycode in layout**: Press the key mapped to `QK_BOOT`.\
In the default keymap it's accessible by pressing either of the buttons bringing you to layer `_SYM` and then pressing one of the outer Ctrl's.