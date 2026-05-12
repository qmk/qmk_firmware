# Valor Rev 3

An Alice replacement keyboard PCB.

* Keyboard Maintainer: [Xelus22](https://github.com/Xelus22)
* Hardware Supported: Valor Rev 3
* Hardware Availability: Custom keyboard group buys

Make example for this keyboard (after setting up your build environment):

    make xelus/valor/rev3:default

Flashing example for this keyboard:

    make xelus/valor/rev3:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the top left key and plug in the keyboard
* **Physical Reset**: The AVR ISP is exposed. Short the RST pad with GND.
* **Keycode in layout**: Press the key mapped to `QK_BOOT`
