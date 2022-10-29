# Epomaker TH66

A 65% keyboard made by Epomaker, which controlled by an Atmega32u4 chipset. The keyboard features per-key RGB, RGB underglow and 1 encoder.

* Keyboard Maintainer: Epomaker
* Hardware Supported: Atmega32u4
* Hardware Availability: https://www.aliexpress.com/item/1005004353520898.html

Make example for this keyboard (after setting up your build environment):

    make epomaker/th66:default

Flashing example for this keyboard:

    make epomaker/th66:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
